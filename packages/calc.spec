Name:           calc
Version:        1.0.0
Release:        1%{?dist}
Summary:        Calculator package script

License:        GPL
Source0:        %{name}-%{version}.tar.gz

Requires:       bash

%description
This is a calculator with most basic mathematical functions

%prep
%setup -q

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_bindir}
cp calc $RPM_BUILD_ROOT/%{_bindir}

%define _rpmdir ./

%clean
rm -rf $RPM_BUILD_ROOT

%global _build_id_links alldebug

%files
%{_bindir}/calc

%changelog
* Thu Jun  06 2024 Kostenko Alisa <lisa103845@gmail.com> - 1.0.0
- First version of calculator being packaged
