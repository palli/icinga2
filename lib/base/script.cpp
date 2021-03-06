/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "base/script.h"
#include "base/scriptlanguage.h"
#include "base/dynamictype.h"
#include "base/logger_fwd.h"
#include "base/objectlock.h"
#include "base/debug.h"

using namespace icinga;

REGISTER_TYPE(Script);

void Script::Start(void)
{
	DynamicObject::Start();

	ASSERT(OwnsLock());

	SpawnInterpreter();
}

String Script::GetLanguage(void) const
{
	ObjectLock olock(this);

	return m_Language;
}

String Script::GetCode(void) const
{
	ObjectLock olock(this);

	return m_Code;
}

void Script::SpawnInterpreter(void)
{
	Log(LogInformation, "base", "Reloading script '" + GetName() + "'");

	ScriptLanguage::Ptr language = ScriptLanguage::GetByName(GetLanguage());
	m_Interpreter = language->CreateInterpreter(GetSelf());
}

void Script::InternalSerialize(const Dictionary::Ptr& bag, int attributeTypes) const
{
	DynamicObject::InternalSerialize(bag, attributeTypes);

	bag->Set("language", m_Language);
	bag->Set("code", m_Code);
}

void Script::InternalDeserialize(const Dictionary::Ptr& bag, int attributeTypes)
{
	DynamicObject::InternalDeserialize(bag, attributeTypes);

	m_Language = bag->Get("language");
	m_Code = bag->Get("code");

}
