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

#include "base/object.h"
#include <boost/test/unit_test.hpp>
#include <boost/smart_ptr/make_shared.hpp>

using namespace icinga;

class TestObject : public Object
{
public:
	typedef boost::shared_ptr<TestObject> Ptr;
	typedef boost::weak_ptr<TestObject> WeakPtr;

	TestObject::Ptr GetTestRef(void)
	{
		return GetSelf();
	}
};

BOOST_AUTO_TEST_SUITE(base_object)

BOOST_AUTO_TEST_CASE(construct)
{
	Object::Ptr tobject = boost::make_shared<TestObject>();
	BOOST_CHECK(tobject);
}

BOOST_AUTO_TEST_CASE(getself)
{
	TestObject::Ptr tobject = boost::make_shared<TestObject>();
	TestObject::Ptr tobject_self = tobject->GetTestRef();
	BOOST_CHECK(tobject == tobject_self);
}

BOOST_AUTO_TEST_CASE(weak)
{
	TestObject::Ptr tobject = boost::make_shared<TestObject>();
	TestObject::WeakPtr wtobject = tobject;
	tobject.reset();
	BOOST_CHECK(!tobject);
	BOOST_CHECK(!wtobject.lock());
}

BOOST_AUTO_TEST_SUITE_END()
