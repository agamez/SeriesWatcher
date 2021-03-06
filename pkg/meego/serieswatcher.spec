# 
# Do not Edit! Generated by:
# spectacle version 0.18
# 
# >> macros
# << macros

Name:       serieswatcher
Summary:    Series Watcher - TV series browser and tracker application.
Version:    0.1.3
Release:    1
Group:      Applications/Productivity
License:    GPLv2
URL:        http://xf.iksaif.net/dev/serieswatcher.html
Source0:    %{name}-%{version}.tar.bz2
Source100:  serieswatcher.yaml
BuildRequires:  pkgconfig(QtCore) >= 4.6.0
BuildRequires:  pkgconfig(QtNetwork)
BuildRequires:  pkgconfig(QtGui)
BuildRequires:  cmake


%description
TV series browser and tracker application. Its goal is to help you manage the TV shows you watch regularly and keep track of the episodes you have seen so far. The shows and episodes can be retrieved automatically by using the “TheTVDB API”.



%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

mkdir meego-qttvdb-build
cd meego-qttvdb-build

cmake ../qttvdb/  \
    -DCMAKE_INSTALL_PREFIX:PATH=%{_prefix} \

make %{?jobs:-j%jobs}

mkdir meego-build
cd meego-build
cmake ..  \
    -DCMAKE_INSTALL_PREFIX:PATH=%{_prefix} \
    -DQTTVDB_LIBRARY_DIRS=%{buildroot}/meego-qttvdb-build/lib/ \
    -DQTTVDB_INCLUDE_DIRS=%{_sourcedir}/qttvdb/src/


make %{?jobs:-j%jobs}

# >> build post
# << build post
%install
rm -rf %{buildroot}
# >> install pre
# << install pre
cd meego-build
%make_install 

# >> install post
# << install post


%post
/bin/touch --no-create %{_datadir}/icons/hicolor || :
%{_bindir}/gtk-update-icon-cache \
  --quiet %{_datadir}/icons/hicolor 2> /dev/null|| :
update-desktop-database %{_datadir}/applications &> /dev/null || :

%postun
/bin/touch --no-create %{_datadir}/icons/hicolor || :
%{_bindir}/gtk-update-icon-cache \
  --quiet %{_datadir}/icons/hicolor 2> /dev/null|| :
update-desktop-database %{_datadir}/applications &> /dev/null || :


%files
%defattr(-,root,root,-)
# >> files
# << files
/usr/bin/serieswatcher
/usr/share/applications/serieswatcher.desktop
/usr/share/icons/hicolor/64x64/apps/serieswatcher.png
/usr/share/icons/hicolor/scalable/apps/serieswatcher.svg
