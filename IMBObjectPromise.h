/*
 iMedia Browser Framework <http://karelia.com/imedia/>
 
 Copyright (c) 2005-2009 by Karelia Software et al.
 
 iMedia Browser is based on code originally developed by Jason Terhorst,
 further developed for Sandvox by Greg Hulands, Dan Wood, and Terrence Talbot.
 The new architecture for version 2.0 was developed by Peter Baumgartner.
 Contributions have also been made by Matt Gough, Martin Wennerberg and others
 as indicated in source files.
 
 The iMedia Browser Framework is licensed under the following terms:
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in all or substantial portions of the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to permit
 persons to whom the Software is furnished to do so, subject to the following
 conditions:
 
	Redistributions of source code must retain the original terms stated here,
	including this list of conditions, the disclaimer noted below, and the
	following copyright notice: Copyright (c) 2005-2009 by Karelia Software et al.
 
	Redistributions in binary form must include, in an end-user-visible manner,
	e.g., About window, Acknowledgments window, or similar, either a) the original
	terms stated here, including this list of conditions, the disclaimer noted
	below, and the aforementioned copyright notice, or b) the aforementioned
	copyright notice and a link to karelia.com/imedia.
 
	Neither the name of Karelia Software, nor Sandvox, nor the names of
	contributors to iMedia Browser may be used to endorse or promote products
	derived from the Software without prior and express written permission from
	Karelia Software or individual contributors, as appropriate.
 
 Disclaimer: THE SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS
 "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 CONTRACT, TORT, OR OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION WITH, THE
 SOFTWARE OR THE USE OF, OR OTHER DEALINGS IN, THE SOFTWARE.
*/


//----------------------------------------------------------------------------------------------------------------------


#pragma mark CONSTANTS
	
extern NSString* kIMBObjectPromiseType;


//----------------------------------------------------------------------------------------------------------------------


#pragma mark 

// An IMBObjectPromise is a abstraction that is sitting between the iMedia framework and the client application. 
// Objects from some parsers reside on the local file system, but objects from other parser may reside on a remote 
// server or a camera device. In these cases we only have lores thumbnails available. To access the hires data, we
// first need to start an asynchronous download operation. To be as lazy as possible, IMBObjectPromise encapsulates
// this access. The frameworks hands the promise to the client app, which can then trigger a download as desired...


@interface IMBObjectPromise : NSObject <NSCopying,NSCoding>
{
	NSArray* _objects; 
	NSString* _downloadFolderPath;
	NSMutableArray* _localFiles;
	NSError* _error;
	
	double _objectCount;
	double _objectIndex;
	
	id _delegate;
	SEL _finishSelector;
}

/// Array of IMBObjects

@property (retain) NSArray* objects;

/// Optional download folder (only needed for remote files that need to be downloaded)

@property (retain) NSString* downloadFolderPath;

/// Array of paths (may contain NSNull objects in case of failure)

@property (retain) NSMutableArray* localFiles;	

/// Retained due to asynchronous nature of the promise

@property (retain) id delegate;			

/// Method with signature - (void) didFinish:(IMBObjectPromise*)inObjectPromise withError:(NSError*)inError

@property (assign) SEL finishSelector;	

/// Contains error in case of failure	
	
@property (retain) NSError* error;				

/// Create a promise with an array of objects

- (id) initWithObjects:(NSArray*)inObjects;

/// Clients can start loading objects asynchronously. Once the finish selector is called the loading is done and local files can be retrieved.

- (void) startLoadingWithDelegate:(id)inDelegate finishSelector:(SEL)inSelector;	
		
@end


//----------------------------------------------------------------------------------------------------------------------


#pragma mark 

/// Protocol that notifies the delegate (usually the client application) of download progress

@protocol IMBObjectPromiseDelegate

@optional

- (BOOL) objectPromiseShouldStartLoadingAsynchronously:(IMBObjectPromise*)inObjectPromise;
- (void) objectPromise:(IMBObjectPromise*)inObjectPromise wantsProgressUI:(BOOL)inWantsProgressUI;
- (void) objectPromise:(IMBObjectPromise*)inObjectPromise loadingProgress:(double)inFraction;
- (void) objectPromise:(IMBObjectPromise*)inObjectPromise didFinishLoadingWithError:(NSError*)inError;

@end


//----------------------------------------------------------------------------------------------------------------------


#pragma mark 

// This subclass is used for local object files that can be returned immediately. In this case a promise isn't 
// really necessary, but to make the architecture more consistent, this abstraction is used nonetheless... 

@interface IMBLocalObjectPromise : IMBObjectPromise

@end


//----------------------------------------------------------------------------------------------------------------------


#pragma mark 

// This subclass is used for remote object files that can be downloaded from a network. NSURLDownload is used to
// pull the object files of the network onto the local file system, where it can then be accessed by the delegate... 

@interface IMBRemoteObjectPromise : IMBObjectPromise
{
	NSMutableDictionary* _urlToLocalFileMap;
}

@property (retain) NSMutableDictionary* urlToLocalFileMap;

@end


//----------------------------------------------------------------------------------------------------------------------
