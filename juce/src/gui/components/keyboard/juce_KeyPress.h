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

#ifndef __JUCE_KEYPRESS_JUCEHEADER__
#define __JUCE_KEYPRESS_JUCEHEADER__

#include "juce_ModifierKeys.h"
#include "../../../text/juce_String.h"


//==============================================================================
/**
    Represents a key press, including any modifier keys that are needed.

    E.g. a KeyPress might represent CTRL+C, SHIFT+ALT+H, Spacebar, Escape, etc.

    @see Component, KeyListener, Button::addShortcut, KeyPressMappingManager
*/
class JUCE_API  KeyPress
{
public:
    //==============================================================================
    /** Creates an (invalid) KeyPress.

        @see isValid
    */
    KeyPress() throw();

    /** Creates a KeyPress for a key and some modifiers.

        e.g.
        CTRL+C would be: KeyPress ('c', ModifierKeys::ctrlModifier)
        SHIFT+Escape would be: KeyPress (KeyPress::escapeKey, ModifierKeys::shiftModifier)

        @param keyCode      a code that represents the key - this value must be
                            one of special constants listed in this class, or an
                            8-bit character code such as a letter (case is ignored),
                            digit or a simple key like "," or ".". Note that this
                            isn't the same as the textCharacter parameter, so for example
                            a keyCode of 'a' and a shift-key modifier should have a
                            textCharacter value of 'A'.
        @param modifiers    the modifiers to associate with the keystroke
        @param textCharacter    the character that would be printed if someone typed
                            this keypress into a text editor. This value may be
                            null if the keypress is a non-printing character
        @see getKeyCode, isKeyCode, getModifiers
    */
    KeyPress (const int keyCode,
              const ModifierKeys& modifiers,
              const juce_wchar textCharacter) throw();

    /** Creates a keypress with a keyCode but no modifiers or text character.
    */
    KeyPress (const int keyCode) throw();

    /** Creates a copy of another KeyPress. */
    KeyPress (const KeyPress& other) = default;

    /** Copies this KeyPress from another one. */
    KeyPress& operator= (const KeyPress& other) = default;

    /** Compares two KeyPress objects. */
    bool operator== (const KeyPress& other) const throw();

    /** Compares two KeyPress objects. */
    bool operator!= (const KeyPress& other) const throw();

    //==============================================================================
    /** Returns true if this is a valid KeyPress.

        A null keypress can be created by the default constructor, in case it's
        needed.
    */
    bool isValid() const throw()                                { return keyCode != 0; }

    /** Returns the key code itself.

        This will either be one of the special constants defined in this class,
        or an 8-bit character code.
    */
    int getKeyCode() const throw()                              { return keyCode; }

    /** Returns the key modifiers.

        @see ModifierKeys
    */
    const ModifierKeys getModifiers() const throw()             { return mods; }

    /** Returns the character that is associated with this keypress.

        This is the character that you'd expect to see printed if you press this
        keypress in a text editor or similar component.
    */
    juce_wchar getTextCharacter() const throw()                 { return textCharacter; }

    /** Checks whether the KeyPress's key is the same as the one provided, without checking
        the modifiers.

        The values for key codes can either be one of the special constants defined in
        this class, or an 8-bit character code.

        @see getKeyCode
    */
    bool isKeyCode (const int keyCodeToCompare) const throw()   { return keyCode == keyCodeToCompare; }

    //==============================================================================
    /** Converts a textual key description to a KeyPress.

        This attempts to decode a textual version of a keypress, e.g. "CTRL + C" or "SPACE".

        This isn't designed to cope with any kind of input, but should be given the
        strings that are created by the getTextDescription() method.

        If the string can't be parsed, the object returned will be invalid.

        @see getTextDescription
    */
    static const KeyPress createFromDescription (const String& textVersion) throw();

    /** Creates a textual description of the key combination.

        e.g. "CTRL + C" or "DELETE".

        To store a keypress in a file, use this method, along with createFromDescription()
        to retrieve it later.
    */
    const String getTextDescription() const throw();

    //==============================================================================
    /** Checks whether the user is currently holding down the keys that make up this
        KeyPress.

        Note that this will return false if any extra modifier keys are
        down - e.g. if the keypress is CTRL+X and the user is actually holding CTRL+ALT+x
        then it will be false.
    */
    bool isCurrentlyDown() const throw();

    /** Checks whether a particular key is held down, irrespective of modifiers.

        The values for key codes can either be one of the special constants defined in
        this class, or an 8-bit character code.
    */
    static bool isKeyCurrentlyDown (int keyCode) throw();

    //==============================================================================
    // Key codes
    //
    // Note that the actual values of these are platform-specific and may change
    // without warning, so don't store them anywhere as constants. For persisting/retrieving
    // KeyPress objects, use getTextDescription() and createFromDescription() instead.
    //

    static const int spaceKey;      /**< key-code for the space bar */
    static const int escapeKey;     /**< key-code for the escape key */
    static const int returnKey;     /**< key-code for the return key*/
    static const int tabKey;        /**< key-code for the tab key*/

    static const int deleteKey;     /**< key-code for the delete key (not backspace) */
    static const int backspaceKey;  /**< key-code for the backspace key */
    static const int insertKey;     /**< key-code for the insert key */

    static const int upKey;         /**< key-code for the cursor-up key */
    static const int downKey;       /**< key-code for the cursor-down key */
    static const int leftKey;       /**< key-code for the cursor-left key */
    static const int rightKey;      /**< key-code for the cursor-right key */
    static const int pageUpKey;     /**< key-code for the page-up key */
    static const int pageDownKey;   /**< key-code for the page-down key */
    static const int homeKey;       /**< key-code for the home key */
    static const int endKey;        /**< key-code for the end key */

    static const int F1Key;         /**< key-code for the F1 key */
    static const int F2Key;         /**< key-code for the F2 key */
    static const int F3Key;         /**< key-code for the F3 key */
    static const int F4Key;         /**< key-code for the F4 key */
    static const int F5Key;         /**< key-code for the F5 key */
    static const int F6Key;         /**< key-code for the F6 key */
    static const int F7Key;         /**< key-code for the F7 key */
    static const int F8Key;         /**< key-code for the F8 key */
    static const int F9Key;         /**< key-code for the F9 key */
    static const int F10Key;        /**< key-code for the F10 key */
    static const int F11Key;        /**< key-code for the F11 key */
    static const int F12Key;        /**< key-code for the F12 key */
    static const int F13Key;        /**< key-code for the F13 key */
    static const int F14Key;        /**< key-code for the F14 key */
    static const int F15Key;        /**< key-code for the F15 key */
    static const int F16Key;        /**< key-code for the F16 key */

    static const int numberPad0;     /**< key-code for the 0 on the numeric keypad. */
    static const int numberPad1;     /**< key-code for the 1 on the numeric keypad. */
    static const int numberPad2;     /**< key-code for the 2 on the numeric keypad. */
    static const int numberPad3;     /**< key-code for the 3 on the numeric keypad. */
    static const int numberPad4;     /**< key-code for the 4 on the numeric keypad. */
    static const int numberPad5;     /**< key-code for the 5 on the numeric keypad. */
    static const int numberPad6;     /**< key-code for the 6 on the numeric keypad. */
    static const int numberPad7;     /**< key-code for the 7 on the numeric keypad. */
    static const int numberPad8;     /**< key-code for the 8 on the numeric keypad. */
    static const int numberPad9;     /**< key-code for the 9 on the numeric keypad. */

    static const int numberPadAdd;            /**< key-code for the add sign on the numeric keypad. */
    static const int numberPadSubtract;       /**< key-code for the subtract sign on the numeric keypad. */
    static const int numberPadMultiply;       /**< key-code for the multiply sign on the numeric keypad. */
    static const int numberPadDivide;         /**< key-code for the divide sign on the numeric keypad. */
    static const int numberPadSeparator;      /**< key-code for the comma on the numeric keypad. */
    static const int numberPadDecimalPoint;   /**< key-code for the decimal point sign on the numeric keypad. */
    static const int numberPadEquals;         /**< key-code for the equals key on the numeric keypad. */
    static const int numberPadDelete;         /**< key-code for the delete key on the numeric keypad. */

    static const int playKey;        /**< key-code for a multimedia 'play' key, (not all keyboards will have one) */
    static const int stopKey;        /**< key-code for a multimedia 'stop' key, (not all keyboards will have one) */
    static const int fastForwardKey; /**< key-code for a multimedia 'fast-forward' key, (not all keyboards will have one) */
    static const int rewindKey;      /**< key-code for a multimedia 'rewind' key, (not all keyboards will have one) */

    juce_UseDebuggingNewOperator

private:
    //==============================================================================
    int keyCode;
    ModifierKeys mods;
    juce_wchar textCharacter;
};


#endif   // __JUCE_KEYPRESS_JUCEHEADER__
