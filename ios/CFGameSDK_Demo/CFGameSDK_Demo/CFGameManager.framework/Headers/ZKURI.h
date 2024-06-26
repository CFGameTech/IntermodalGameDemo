//
//  ZKURI.h
//

#import <Foundation/Foundation.h>
#import "ZKURIComponents.h"
#import "ZKURIQuery.h"

@interface ZKURI : NSObject

/**
 Initialize a `KCURI` with a URL.
 
 If the url string from the NSURL is malformed, nil is returned.
 
 If `resolve` is `YES` and `url` is a relative URL, the components of `[url absoluteURL]`
 are used. As a general rule, clients should pass in `YES` unless they're
 specifically interested in the components of only the relative portion of a
 relative URL.
 
 @param url The URL.
 @param resolve Whether to resolve relative URLs
 */
- (instancetype)initWithURL:(NSURL *)aUrl resolvingAgainstBaseURL:(BOOL)aIsResolve;


/**
 Initialize a `KCURI` with a URL string.
 
 If the URLString is malformed, `nil` is returned.
 */
- (instancetype)initWithString:(NSString *)aURLString;
- (instancetype)initWithString:(NSString *)aURLString relativeToURI:(ZKURI*)aBaseURI;

+ (instancetype)URIWithString:(NSString*)aURLString;
+ (instancetype)URIWithString:(NSString*)aURLString relativeToURI:(ZKURI*)aBaseURI;

/**
 parse the uri string to KCURI
 
 @param aUriString  is uri string
 */
+(ZKURI*) parse:(NSString*)aUriString;


/**
 Returns a KCURI created from the `KCURI` relative to a base URI.
 
 If the `KCURIComponents` has an authority component (user, password, host or port)
 and a path component, then the path must either begin with `/` or be an empty
 string. If the `KCURIComponents` does not have an authority component (user, password, host or port)
 and has a path component, the path component must not start with `//`. If those
 requirements are not met, `nil` is returned.
 */
- (ZKURI*)URIRelativeToURL:(ZKURI*)aBaseURL;


/**
 Returns a KCURIComponents
 */
-(ZKURIComponents*)components;

/**
 Returns a KCURIQuery
 */
-(ZKURIQuery*)query;

/**
 Returns aDictionary
 */
-(NSDictionary*)getQueries;


/**
 Returns a URL created from the `KCURIComponents`.
 
 If the `KCURIComponents` has an authority component (user, password, host or port)
 and a path component, then the path must either begin with `/` or be an empty
 string. If the `KCURIComponents` does not have an authority component (user, password, host or port)
 and has a path component, the path component must not start with `//`. If those
 requirements are not met, `nil` is returned.
 */
- (NSURL *)URL;


/**
 Returns the uri is absolute
 */
- (BOOL)isAbsolute;

/**
 Returns the uri is relative
 */
- (BOOL)isRelative;

/**
 * Gets the decoded path segments.
 *
 * @return decoded path segments, each without a leading or trailing '/'
 */
- (NSArray*)getPathSegments;

/**
 * Gets the decoded last segment in the path.
 *
 * @return the decoded last segment or nil if the path is empty
 */
- (NSString*)getLastPathSegment;

- (NSString*)description;

@end
