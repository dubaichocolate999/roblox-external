#pragma once

#include <string>
#include "utils/driver/driver.h"
#include "utils/offsets.h"

namespace roblox {
	static std::string read_string(uintptr_t address) {
		const auto size = read<uintptr_t>(address + offsets::NameSize);

		if (size >= offsets::NameSize)
			address = read<uintptr_t>(address);

		std::string content;
		BYTE code;

		for (std::int32_t index = 0; code = read<std::uint8_t>(address + index); index++)
			content.push_back(code);

		return content;
	}

	static void write_string(uintptr_t address, const std::string& string) {
		const auto size = read<uintptr_t>(address + offsets::NameSize);

		if (size >= offsets::NameSize)
			address = read<uintptr_t>(address);

		write_bytes(address, (PVOID)string.c_str(), (ULONG)string.length());
	}


	static std::string get_name(uintptr_t address) {
		uintptr_t nameptr = read<uintptr_t>(address + offsets::Name);

		std::string name;
		const auto size = read<int>(nameptr + offsets::NameSize);

		if (size >= 16) {
			uintptr_t nameptr2 = read<uintptr_t>(nameptr);
			while (read<char>(nameptr2) != '\0') {
				name += read<char>(nameptr2);
				nameptr2++;
			}
		}
		else
			name = read<std::string>(nameptr);

		return name;
	}

	static std::vector<uintptr_t> get_children(uintptr_t address) {
		std::vector<uintptr_t> children;
		uintptr_t ptr = read<uintptr_t>(address + offsets::Children);
		uintptr_t end = read<uintptr_t>(ptr + offsets::ChildrenEnd);

		for (auto i = read<uintptr_t>(ptr); i < end; i += offsets::NameSize)
			children.push_back(read<uintptr_t>(i));

		return children;
	}

	static uintptr_t find_first_child(uintptr_t address, std::string name) {
		for (auto child : get_children(address)) {
			if (get_name(child) == name)
				return child;
		}

		return 0;
	}

	static std::string get_class_name(uintptr_t address)
	{
		const auto descriptor = read<uintptr_t>(address + offsets::ClassDescriptor);
		const auto end = read<uintptr_t>(descriptor + offsets::ChildrenEnd);

		if (end)
			return read_string(end);

		return "";
	}

	static uintptr_t find_first_child_class(uintptr_t address, std::string classname) {
		for (auto child : get_children(address)) {
			if (get_class_name(child) == classname)
				return child;
		}

		return 0;
	}
}