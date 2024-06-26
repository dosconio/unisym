// ASCII C++ TAB4 CRLF
// Attribute: <ArnCovenant> <Env> <bin^%> <CPU()> [Allocation]
// LastCheck: 
// AllAuthor: @dosconio
// ModuTitle: D-D- Node for C++
/*
	Copyright 2023 ArinaMgk

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0
	http://unisym.org/license.html

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include "../../../inc/cpp/cinc"
#include "../../../inc/c/ustring.h"
#include "../../../inc/cpp/cinc"
#include "../../../inc/cpp/dnode"

namespace uni {

#define tmpl(...) __VA_ARGS__ DnodeChain

	tmpl()::DnodeChain(bool need_free) {
		node_count = 0;
		root_node = nullptr;
		last_node = nullptr;
		need_free_content = need_free;
		_node_freefunc = 0;
		sorted = false;
		little_endian = true;
		free_pass_whole = true;
		_node_compare = 0;//{MAYBE} _defa_compare, to simplify the below
	}

	tmpl()::~DnodeChain() {
		if (nullptr == root_node) return;
		Dnode* next = (Dnode*)root_node;
		while (next = Remove(next, false));
	}

	Dnode* DnodeChain::Remove(Dnode* content, bool systematic) {
		if (!content) return 0;
		Dnode* ret_next = content->next;
		if (systematic) {
			if (content->left) content->left->next = ret_next;
			if (ret_next) ret_next->left = content->left;
		}
		dchainfree(content, this->);
		return ret_next;
	}

	//{TODO}
	tmpl(void)::Append(void* addr, stduint typ) {
		Dnode* tmp = zalcof(Dnode);
		tmp->offs = addr;
		tmp->type = typ;
		tmp->next = nullptr;
		tmp->left = (Dnode*)last_node;
		node_count++;
		if (nullptr == root_node)
		{
			last_node = root_node = tmp;
		}
		// if (aflaga.autosort)
		// else if (_node_compare)
		else
		{
			last_node = ((Dnode*)last_node)->next = tmp;
		}
	}

	Dnode* DnodeChain::Index(void* content) {
		Dnode* nod = Root();
		if (nod) do {
			if (nod->offs == content)
				return nod;
		} while (nod = nod->next);
		return 0;
	}

	bool DnodeChain::Match(void* off, stduint typ) {
		Dnode* nod = Root();
		if (nod) do {
			if (nod->offs == off && nod->type == typ)
				return true;
		} while (nod = nod->next);
		return false;
	}

#undef tmpl
}
