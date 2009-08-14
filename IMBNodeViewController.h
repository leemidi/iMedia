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


#pragma mark ABSTRACT

// This subclass of NSViewController is responsible for the splitview and the outline view which shows the library 
// nodes (upper half of the window). It loads the views and is also responsible for handling selection and expansion  
// of nodes, and for making sure that the state is persistent across application launches. 

// Please note that this controller is the delegate of all views, so do not modify those delegates. If you do need
// delegate messages for various events, then use the delegate methods of IMBLibraryController...

// There is an instance of this controller per window and per media type. If we have 4 media types (photos, music,
// video, links) and 3 windows containing media browser UI, then we need 12 instances of this controller. This 
// controller coordinates between the views and the IMBLibraryController. Essentially IMBLibraryController is a 
// backend controller, while IMBNodeViewController is a frontend controller.


//----------------------------------------------------------------------------------------------------------------------


#pragma mark CLASSES

@class IMBLibraryController;
@class IMBNodeTreeController;
@class IMBOutlineView;
@class IMBParser;
@class IMBNode;


//----------------------------------------------------------------------------------------------------------------------


#pragma mark 


@interface IMBNodeViewController : NSViewController
{
	IMBLibraryController* _libraryController;
	NSString* _selectedNodeIdentifier;
	NSMutableArray* _expandedNodeIdentifiers;
	BOOL _isRestoringState;
	IMBParser* _selectedParser;
	
	IBOutlet NSSplitView* ibSplitView;
	IBOutlet IMBNodeTreeController* ibNodeTreeController;
	IBOutlet IMBOutlineView* ibNodeOutlineView;
	IBOutlet NSPopUpButton* ibNodePopupButton;
	IBOutlet NSView* ibObjectContainerView;
}

+ (IMBNodeViewController*) viewControllerForLibraryController:(IMBLibraryController*)inLibraryController;

// Library...

@property (retain) IMBLibraryController* libraryController;
@property (readonly) NSString* mediaType;

// Nodes (sourcelist)...

@property (readonly) IMBNodeTreeController* nodeTreeController;
@property (readonly) IMBOutlineView* nodeOutlineView;
@property (readonly) NSPopUpButton* nodePopupButton;
@property (readonly) NSView* objectContainerView;

@property (retain) NSString* selectedNodeIdentifier;
@property (retain) NSMutableArray* expandedNodeIdentifiers;
- (void) selectNode:(IMBNode*)inNode;
@property (readonly) IMBNode* selectedNode;
@property (retain) IMBParser* selectedParser;

// Context menu support...

- (NSMenu*) menuForNode:(IMBNode*)inNode;
- (NSMenu*) menuForBackground;

// Actions...

- (BOOL) canReloadNode;
- (IBAction) reloadNode:(id)inSender;

- (BOOL) canAddNode;
- (IBAction) addNode:(id)inSender;

- (BOOL) canRemoveNode;
- (IBAction) removeNode:(id)inSender;

@end


//----------------------------------------------------------------------------------------------------------------------
