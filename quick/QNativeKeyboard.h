#ifndef __Q_NativeKeyboard_H
#define __Q_NativeKeyboard_H

#include <string.h>

#include "s3eKeyboard.h"

#include "QLuaHelpers.h"

// tolua_begin
namespace nativeKeyboard {

	int32 handler(void*, void*);

	/**
	 * Shows native keyboard
	 * @return true for now. TODO: return something meaningful
	 */
	bool showKeyboard();

	/**
	 * Hides native keyboard
	 */
	void hideKeyboard();
}
// tolua_end

#endif // __Q_NativeKeyboard_H