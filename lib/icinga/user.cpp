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

#include "i2-icinga.h"

using namespace icinga;

REGISTER_TYPE(User);

User::User(const Dictionary::Ptr& properties)
	: DynamicObject(properties)
{
	RegisterAttribute("display_name", Attribute_Config, &m_DisplayName);
	RegisterAttribute("macros", Attribute_Config, &m_Macros);
	RegisterAttribute("groups", Attribute_Config, &m_Groups);
}

User::~User(void)
{
	UserGroup::InvalidateMembersCache();
}

/**
 * @threadsafety Always.
 */
void User::OnAttributeChanged(const String& name)
{
	assert(!OwnsLock());

	if (name == "groups")
		UserGroup::InvalidateMembersCache();
}

/**
 * @threadsafety Always.
 */
User::Ptr User::GetByName(const String& name)
{
	DynamicObject::Ptr configObject = DynamicObject::GetObject("User", name);

	return dynamic_pointer_cast<User>(configObject);
}

/**
 * @threadsafety Always.
 */
String User::GetDisplayName(void) const
{
	if (!m_DisplayName.IsEmpty())
		return m_DisplayName;
	else
		return GetName();
}

/**
 * @threadsafety Always.
 */
Dictionary::Ptr User::GetGroups(void) const
{
	return m_Groups;
}

/**
 * @threadsafety Always.
 */
Dictionary::Ptr User::GetMacros(void) const
{
	return m_Macros;
}

/**
 * @threadsafety Always.
 */
Dictionary::Ptr User::CalculateDynamicMacros(void) const
{
	Dictionary::Ptr macros = boost::make_shared<Dictionary>();

	macros->Set("CONTACTNAME", GetName());
	macros->Set("CONTACTALIAS", GetName());

	macros->Seal();

	return macros;
}