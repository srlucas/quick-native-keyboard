#include "QNativeKeyboard.h"

#include <string.h>

#include "s3eKeyboard.h"

#include "QLuaHelpers.h"

// namespace nativeKeyboard {

    /**
     * Callback function to handle key events.
     *
     * for each character pressed, we will send an event to the LUA layer.
     *
     * @param  sys [description]
     * @param  a   [description]
     * @return     [description]
     */
	int32 nativeKeyboard::handler(void* sys, void* a) {

	    s3eKeyboardCharEvent* event = (s3eKeyboardCharEvent*)sys;

		IwDebugTraceLinePrintf("Native Keyboard: Key down [%c]\n", event->m_Char);

		char * buffer = (char *) malloc(MB_CUR_MAX);
		char * orig = (char *) malloc (MB_CUR_MAX);

 		int length = wctomb(buffer, event->m_Char);
 		sprintf(orig, "%c", event->m_Char);

 		char * cmd = "";

 		if (event->m_Char == 0x08) {
			IwDebugTraceLinePrintf("Native Keyboard: Detected backspace");
			cmd = "BACKSPACE";
 		}
 		if (event->m_Char == 0x0a) {
			IwDebugTraceLinePrintf("Native Keyboard: Detected ENTER");
			cmd = "ENTER";
 		}

		IwDebugTraceLinePrintf("About to throw char_event. Wide: [%s], Multibyte: [%s]\n", orig, buffer);

		// throw lua event
		quick::LUA_EVENT_PREPARE("char_event");
		quick::LUA_EVENT_SET_STRING("regular_char", orig);
		quick::LUA_EVENT_SET_STRING("multibyte_char", buffer);
		quick::LUA_EVENT_SET_STRING("command", cmd);
		quick::LUA_EVENT_SEND();
		lua_pop(quick::g_L, 1);
		IwDebugTraceLinePrintf("char_event already thrown\n");

		// cleanup
		free(buffer);
		free(orig);

	    return true;
	}

	/**
	 * Show native keyboard
	 *
	 * @return true if showing keyboard was successfull. False if not.
	 */
    bool nativeKeyboard::showKeyboard() {
		bool result = false;

		IwDebugTraceLinePrintf("Registering keyboard listeing for char event");
	    // s3eResult res = s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, handler, NULL);
	    s3eResult res = s3eKeyboardRegister(S3E_KEYBOARD_CHAR_EVENT, handler, NULL);


	    if (res == S3E_RESULT_SUCCESS) {
			IwDebugTraceLinePrintf("Registering keyboard response: SUCCESS");
			result = true;
	    }
	    if (res == S3E_RESULT_ERROR) {
			IwDebugTraceLinePrintf("Registering keyboard response: ERROR");
			result = false;
	    }

		IwDebugTraceLinePrintf("Showing keyboard");
        s3eKeyboardSetInt(S3E_KEYBOARD_GET_CHAR, 1);

        return result;
    }

    /**
     * Hides keyboard.
     *
     * Should we Unregister?
     */
    void nativeKeyboard::hideKeyboard() {
		IwDebugTraceLinePrintf("Hiding keyboard");

        s3eKeyboardSetInt(S3E_KEYBOARD_GET_CHAR, 0);
    }

// } // namespace nativeKeyboard