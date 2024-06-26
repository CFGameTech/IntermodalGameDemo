//
//  ZKURIComponents.h
//

#import <Foundation/Foundation.h>


typedef NS_OPTIONS(NSUInteger, KCURIQueryParameterDecodingOptions) {
    KCURIQueryParameterDecodingPlusAsSpace = 1UL << 0,    // + characters are interpreted as spaces, rather than regular + symbols
};

//you can use KCUtilURL

@interface ZKURIQuery : NSObject
{
  @private
    NSString* m_percentEncodedString;
}

#pragma mark Convenience
+ (NSString *)encodeParameters:(NSDictionary *)aParameters;
+ (NSDictionary *)decodeString:(NSString *)aPercentEncodedQuery options:(KCURIQueryParameterDecodingOptions)aOptions;
+ (NSDictionary *)parametersFromURL:(NSURL *)aUrl options:(KCURIQueryParameterDecodingOptions)aOptions;
+ (NSDictionary *)parametersFromURL:(NSURL *)aUrl;


#pragma mark Creating a KCURIQuery
+ (instancetype)queryWithURL:(NSURL *)aUrl;
- (id)initWithPercentEncodedString:(NSString *)aString;


#pragma mark Decoding Parameters

/**
 Converts the query into a dictionary representation.
 
 For example:
 
 http://example.com?key=value&foo=bar
 
 can be interpreted as:
 
 @{ @"key" : @"value", @"foo" : @"bar" }
 
 Keys and values are percent decoded according to `options`.
 
 If you have a query which doesn't match `NSDictionary`'s design, drop down to
 the primitive `-enumerateParametersWithOptions:usingBlock:` method instead.
 
 @param options A mask that specifies options for parameter decoding.
 @return `nil` if query doesn't neatly fit an `NSDictionary` representation
 */
- (NSDictionary *)parametersWithOptions:(KCURIQueryParameterDecodingOptions)aOptions;

/**
 Enumerates the receiver's parameters, handling cases where an NSDictionary representation doesn't suffice.
 
 * Parameters are reported in the order they appear in the URL
 * Keys and values are percent decoded for your convenience
 * Parameters without a value are reported as `nil`
 * Duplicate parameters are correctly reported too
 
 @param options A mask that specifies options for parameter decoding.
 @param block A block called for each parameter of the query.
 */
- (void)enumerateParametersWithOptions:(KCURIQueryParameterDecodingOptions)aOptions usingBlock:(void (^)(NSString* aKey, NSString* aValue, BOOL* aStop))block __attribute((nonnull(2)));


#pragma mark Encoding Parameters

/**
 Replaces any existing query by encoding the `parameters` dictionary.
 
 For example:
 
 @{ @"key" : @"value", @"foo" : @"bar" }
 
 can be represented as:
 
 http://example.com?key=value&foo=bar
 
 See `-addParameter:value:` for full details on encoding of keys and values.
 
 Parameters are encoded in alphabetical order (of keys) for consistency across
 platforms and OS releases. If ordering is important to your use case, or you
 particularly need to eke out a little more performance, use `-addParameter:value:`
 directly instead.
 
 @param parameters A dictionary to encode, whose keys and values are all strings.
 */
- (void)setParameters:(NSDictionary *)aParameters;

/**
 Adds an extra parameter to end of the receiver.
 
 Enables the query to be built up piece-by-piece. This can be especially useful
 when the ordering of parameters is critical, and/or parameters appear more than
 once.
 
 Both the key and value are percent encoded.
 
 `value` is sent a `-description` message to obtain a string representation
 suitable for encoding, enabling objects like `NSNumber`s to be easily encoded,
 as well as strings.
 */
- (void)addParameter:(NSString *)aKey value:(id <NSObject>)aValue __attribute((nonnull(1)));

/**
 @result The encoded representation of the receiver.
 
 Generally you then pass the result of this method to `NSURLComponents.percentEncodedQuery`
 (or `KCURIComponents`) to build up a full URL.
 */
@property(atomic, readonly, copy) NSString *percentEncodedString;


@end
