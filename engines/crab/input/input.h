/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#ifndef CRAB_INPUT_H
#define CRAB_INPUT_H

#include "backends/keymapper/action.h"
#include "backends/keymapper/keymapper.h"
#include "backends/keymapper/standard-actions.h"

namespace Crab {

namespace pyrodactyl {
namespace input {
enum InputType {
	IT_NONE = -1,

	// Game related input values
	IG_UP,
	IG_DOWN,
	IG_RIGHT,
	IG_LEFT,
	IG_TALK,
	IG_MAP,
	IG_JOURNAL,
	IG_INVENTORY,
	IG_CHARACTER,
	IG_PAUSE,
	IG_QUICKSAVE,
	IG_QUICKLOAD,
	IG_ATTACK,
	IG_BLOCK,

	// UI related input values
	IU_UP,
	IU_DOWN,
	IU_RIGHT,
	IU_LEFT,
	IU_ACCEPT,
	IU_BACK,
	IU_NEXT,
	IU_PREV,
	IU_REPLY_0,
	IU_REPLY_1,
	IU_REPLY_2,
	IU_REPLY_3,
	IU_REPLY_4,
	IU_REPLY_5,
	IU_PAGE_NEXT,
	IU_PAGE_PREV,

	IT_TOTAL
};

enum KeyBindingMode {
	KBM_GAME = 0,
	KBM_UI = 1
};

// Constants related to menu size
const int IG_START = IG_UP, IG_SIZE = IG_BLOCK - IG_START + 1;
const int IU_START = IU_UP, IU_SIZE = IT_TOTAL - IU_START;

class InputManager {
	// Load key configuration from file
	void load(const Common::String &filename);

	// The current version of the input scheme
	uint _version;

	// The current mode of keymap applied
	KeyBindingMode _keyMode;

	// The keybinds in string format for hotkeys and other places
	Common::String _keyDescs[IT_TOTAL];

public:
	InputManager() {
		_version = 0;
		_keyMode = KBM_GAME;

		clearInputs();
	}

	~InputManager() {}

	static Common::Keymap *getDefaultKeyMapsForGame();
	static Common::Keymap *getDefaultKeyMapsForUI();
	static Common::Keymap *getDefaultKeyMapsForHUD();

	void clearInputs() {
		for (int i = 0; i < IT_TOTAL; i++)
			_ivState[i] = false;
	}

	void populateKeyTable();

	void setKeyBindingMode(KeyBindingMode mode);

	KeyBindingMode getKeyBindingMode() const {
		return _keyMode;
	}

	// NOTE: The lower level arrays can have buttons in common, but buttons cannot be common within these arrays
	// Ex. UI and Fight can have buttons in common, but not two keys within UI

	// Inputs used in the game
	Common::String _iv[IT_TOTAL];
	bool _ivState[IT_TOTAL];

	// These functions return true if key is pressed, false otherwise
	bool state(const InputType &val);

	Common::String getAssociatedKey(const InputType &type);
};

} // End of namespace input
} // End of namespace pyrodactyl

} // End of namespace Crab

#endif // CRAB_INPUT_H
