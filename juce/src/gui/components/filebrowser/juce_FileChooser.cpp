/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "../../../core/juce_StandardHeader.h"

#if JUCE_LINUX
  #include <unistd.h>
#endif

BEGIN_JUCE_NAMESPACE

#include "juce_FileChooser.h"
#include "juce_WildcardFileFilter.h"
#include "juce_FileChooserDialogBox.h"
#include "../lookandfeel/juce_LookAndFeel.h"
#include "../windows/juce_AlertWindow.h"


//==============================================================================
FileChooser::FileChooser (const String& chooserBoxTitle,
                          const File& currentFileOrDirectory,
                          const String& fileFilters,
                          const bool useNativeDialogBox_)
    : title (chooserBoxTitle),
      filters (fileFilters),
      startingFile (currentFileOrDirectory),
      useNativeDialogBox (useNativeDialogBox_)
{
#if JUCE_LINUX
    const char* command = "zenity --help";
    if (execlp (command, command, NULL) != 0)
        useNativeDialogBox = false;
#endif

    if (! fileFilters.containsNonWhitespaceChars())
        filters = T("*");
}

FileChooser::~FileChooser()
{
}

bool FileChooser::browseForFileToOpen (FilePreviewComponent* previewComponent)
{
    return showDialog (false, true, false, false, false, previewComponent);
}

bool FileChooser::browseForMultipleFilesToOpen (FilePreviewComponent* previewComponent)
{
    return showDialog (false, true, false, false, true, previewComponent);
}

bool FileChooser::browseForMultipleFilesOrDirectories (FilePreviewComponent* previewComponent)
{
    return showDialog (true, true, false, false, true, previewComponent);
}

bool FileChooser::browseForFileToSave (const bool warnAboutOverwritingExistingFiles)
{
    return showDialog (false, true, true, warnAboutOverwritingExistingFiles, false, 0);
}

bool FileChooser::browseForDirectory()
{
    return showDialog (true, false, false, false, false, 0);
}

const File FileChooser::getResult() const
{
    // if you've used a multiple-file select, you should use the getResults() method
    // to retrieve all the files that were chosen.
    jassert (results.size() <= 1);

    const File* const f = results.getFirst();

    if (f != 0)
        return *f;

    return File::nonexistent;
}

const OwnedArray <File>& FileChooser::getResults() const
{
    return results;
}

bool FileChooser::showDialog (const bool selectsDirectories,
                              const bool selectsFiles,
                              const bool isSave,
                              const bool warnAboutOverwritingExistingFiles,
                              const bool selectMultipleFiles,
                              FilePreviewComponent* const previewComponent)
{
    ScopedPointer <ComponentDeletionWatcher> currentlyFocusedChecker;
    Component* const currentlyFocused = Component::getCurrentlyFocusedComponent();

    if (currentlyFocused != 0)
        currentlyFocusedChecker = new ComponentDeletionWatcher (currentlyFocused);

    results.clear();

    // the preview component needs to be the right size before you pass it in here..
    jassert (previewComponent == 0 || (previewComponent->getWidth() > 10
                                        && previewComponent->getHeight() > 10));

#if JUCE_WINDOWS
    if (useNativeDialogBox && ! (selectsFiles && selectsDirectories))
#elif JUCE_MAC
    if (useNativeDialogBox && (previewComponent == 0))
#else
    if (false)
#endif
    {
        showPlatformDialog (results, title, startingFile, filters,
                            selectsDirectories, selectsFiles, isSave,
                            warnAboutOverwritingExistingFiles,
                            selectMultipleFiles,
                            previewComponent);
    }
    else
    {
        WildcardFileFilter wildcard (selectsFiles ? filters : String::empty,
                                     selectsDirectories ? "*" : String::empty,
                                     String::empty);

        int flags = isSave ? FileBrowserComponent::saveMode
                           : FileBrowserComponent::openMode;

        if (selectsFiles)
            flags |= FileBrowserComponent::canSelectFiles;

        if (selectsDirectories)
            flags |= FileBrowserComponent::canSelectDirectories;

        if (selectMultipleFiles)
            flags |= FileBrowserComponent::canSelectMultipleItems;

        FileBrowserComponent browserComponent (flags, startingFile, &wildcard, previewComponent);

        FileChooserDialogBox box (title, String::empty,
                                  browserComponent,
                                  warnAboutOverwritingExistingFiles,
                                  browserComponent.findColour (AlertWindow::backgroundColourId));

        if (box.show())
        {
            for (int i = 0; i < browserComponent.getNumSelectedFiles(); ++i)
                results.add (new File (browserComponent.getSelectedFile (i)));
        }
    }

    if (currentlyFocused != 0 && ! currentlyFocusedChecker->hasBeenDeleted())
        currentlyFocused->grabKeyboardFocus();

    return results.size() > 0;
}

//==============================================================================
FilePreviewComponent::FilePreviewComponent()
{
}

FilePreviewComponent::~FilePreviewComponent()
{
}


END_JUCE_NAMESPACE
