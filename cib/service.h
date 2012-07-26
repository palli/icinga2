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

#ifndef SERVICE_H
#define SERVICE_H

namespace icinga
{

enum ServiceState
{
	StateOK,
	StateWarning,
	StateCritical,
	StateUnknown,
	StateUncheckable,
};

enum ServiceStateType
{
	StateTypeSoft,
	StateTypeHard
};

class CheckResult;
class CheckResultMessage;
class ServiceStatusMessage;

class I2_CIB_API Service : public ConfigObjectAdapter
{
public:
	Service(const ConfigObject::Ptr& configObject);

	static bool Exists(const string& name);
	static Service GetByName(const string& name);

	string GetAlias(void) const;
	Host GetHost(void) const;
	Dictionary::Ptr GetMacros(void) const;
	string GetCheckCommand(void) const;
	long GetMaxCheckAttempts(void) const;
	long GetCheckInterval(void) const;
	long GetRetryInterval(void) const;
	Dictionary::Ptr GetDependencies(void) const;
	void GetDependenciesRecursive(const Dictionary::Ptr& result) const;
	Dictionary::Ptr GetGroups(void) const;
	Dictionary::Ptr GetCheckers(void) const;

	bool IsReachable(void) const;

	long GetSchedulingOffset(void);
	void SetSchedulingOffset(long offset);
	
	void SetNextCheck(double nextCheck);
	double GetNextCheck(void);
	void UpdateNextCheck(void);

	void SetChecker(const string& checker);
	string GetChecker(void) const;

	bool IsAllowedChecker(const string& checker) const;

	void SetCurrentCheckAttempt(long attempt);
	long GetCurrentCheckAttempt(void) const;

	void SetState(ServiceState state);
	ServiceState GetState(void) const;

	void SetStateType(ServiceStateType type);
	ServiceStateType GetStateType(void) const;

	bool HasLastCheckResult(void) const;
	void SetLastCheckResult(const CheckResult& result);
	CheckResult GetLastCheckResult(void) const;

	void SetLastStateChange(double ts);
	double GetLastStateChange(void) const;

	void SetLastHardStateChange(double ts);
	double GetLastHardStateChange(void) const;

	void ApplyCheckResult(const CheckResult& cr);

	static ServiceState StateFromString(const string& state);
	static string StateToString(ServiceState state);

	static ServiceStateType StateTypeFromString(const string& state);
	static string StateTypeToString(ServiceStateType state);

	static Dictionary::Ptr ResolveDependencies(Host host, const Dictionary::Ptr& dependencies);

	static boost::signal<void (Service service, const CheckResultMessage&)> OnCheckResultReceived;
};

}

#endif /* SERVICE_H */
