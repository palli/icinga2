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

#include "base/tcpsocket.h"
#include "base/exception.h"
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/exception/errinfo_file_name.hpp>

using namespace icinga;

/**
 * Creates a socket and binds it to the specified service.
 *
 * @param service The service.
 * @param family The address family for the socket.
 */
void TcpSocket::Bind(const String& service, int family)
{
	Bind(String(), service, family);
}

/**
 * Creates a socket and binds it to the specified node and service.
 *
 * @param node The node.
 * @param service The service.
 * @param family The address family for the socket.
 */
void TcpSocket::Bind(const String& node, const String& service, int family)
{
	addrinfo hints;
	addrinfo *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(node.IsEmpty() ? NULL : node.CStr(),
	    service.CStr(), &hints, &result) < 0) {
#ifndef _WIN32
		BOOST_THROW_EXCEPTION(socket_error()
		    << boost::errinfo_api_function("getaddrinfo")
		    << boost::errinfo_errno(errno));
#else /* _WIN32 */
		BOOST_THROW_EXCEPTION(socket_error()
		    << boost::errinfo_api_function("getaddrinfo")
		    << errinfo_win32_error(WSAGetLastError()));
#endif /* _WIN32 */
	}

	int fd = INVALID_SOCKET;

	for (addrinfo *info = result; info != NULL; info = info->ai_next) {
		fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

		if (fd == INVALID_SOCKET)
			continue;

		const int optFalse = 0;
		setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, reinterpret_cast<const char *>(&optFalse), sizeof(optFalse));

#ifndef _WIN32
		const int optTrue = 1;
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&optTrue), sizeof(optTrue));
#endif /* _WIN32 */

		int rc = bind(fd, info->ai_addr, info->ai_addrlen);

		if (rc < 0) {
			closesocket(fd);

			continue;
		}

		SetFD(fd);

		break;
	}

	freeaddrinfo(result);

	if (GetFD() == INVALID_SOCKET)
		BOOST_THROW_EXCEPTION(std::runtime_error("Could not create a suitable socket."));
}

/**
 * Creates a socket and connects to the specified node and service.
 *
 * @param node The node.
 * @param service The service.
 */
void TcpSocket::Connect(const String& node, const String& service)
{
	addrinfo hints;
	addrinfo *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int rc = getaddrinfo(node.CStr(), service.CStr(), &hints, &result);

	if (rc < 0) {
#ifndef _WIN32
		BOOST_THROW_EXCEPTION(socket_error()
		    << boost::errinfo_api_function("getaddrinfo")
		    << boost::errinfo_errno(errno));
#else /* _WIN32 */
		BOOST_THROW_EXCEPTION(socket_error()
		    << boost::errinfo_api_function("getaddrinfo")
		    << errinfo_win32_error(WSAGetLastError()));
#endif /* _WIN32 */
	}

	int fd = INVALID_SOCKET;

	for (addrinfo *info = result; info != NULL; info = info->ai_next) {
		fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

		if (fd == INVALID_SOCKET)
			continue;

		rc = connect(fd, info->ai_addr, info->ai_addrlen);

		if (rc < 0) {
			closesocket(fd);

			continue;
		}

		SetFD(fd);

		break;
	}

	freeaddrinfo(result);

	if (GetFD() == INVALID_SOCKET)
		BOOST_THROW_EXCEPTION(std::runtime_error("Could not connect to remote host."));
}
