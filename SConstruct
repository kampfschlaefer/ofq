#! /usr/bin/env python

## Load the builders in config
env = Environment( tools=['default', 'qt', 'scanreplace' ], toolpath = ['.'] )

if env['QTDIR'].find( '3' ) >= 0:
	env['QTDIR'] = "/usr"
	env['QT_CPPPATH'] = "";
	env['QT_LIB'] = ""


env.Replace( LIBS="" )
env.Replace( LIBPATH="" )

# DEBUG:
#env['CXXFLAGS']+="-Wall -Werror -g -fpic"
# RELEASE:
env['CXXFLAGS']+="-fpic"

def CheckPKGConfig( context, pkgname, version="", all=False ):
	import SCons.Util, os, string

	pkg = pkgname.replace( ".", "" )
	pkg = pkg.replace( "-", "" )
	if pkg != pkgname:
		print pkgname + " changes to " + pkg

	if version == "":
		context.Message( "Checking for " + pkgname + "..." )
		ret = context.TryAction( 'pkg-config --exists ' + pkgname )
	else:
		context.Message( "Checking for " + pkgname + " " + version + " or higher..." )
		ret = context.TryAction( "pkg-config --atleast-version=" + version + " " + pkgname )

	if ret[0] == 1:
		tmp = os.popen( 'pkg-config --libs-only-l ' + pkgname ).read().strip()
		if all:
			env.AppendUnique( LIBS = SCons.Util.CLVar( tmp ) )
		else:
			env[pkg + '_LIBS'] = SCons.Util.CLVar( string.replace( tmp, "-l", "" ) )

		tmp = os.popen( 'pkg-config --libs-only-L ' + pkgname ).read().strip()
		if all:
			env.AppendUnique( LIBPATH = SCons.Util.CLVar( string.replace( tmp, "-L", "" ) ) )
		else:
			env[pkg + '_PATHS'] = SCons.Util.CLVar( tmp )

		tmp = ' ' + os.popen( 'pkg-config --cflags ' + pkgname ).read().strip()
		if all:
			env.AppendUnique( CXXFLAGS = SCons.Util.CLVar( tmp ) )
		else:
			env[pkg + '_CFLAGS'] = SCons.Util.CLVar( string.replace( tmp, "-I", "" ) )
	else:
		tmp = "\n" + pkgname
		if version != "":
			tmp += "Version " + version + " or higher"
		print tmp + " is really needed!"
		Exit(1)

	context.Result( ret[0] )
	return ret[0]

conf = Configure( env, custom_tests={'CheckPKGConfig' : CheckPKGConfig }, conf_dir='.cache', log_file='.cache/config.log' )
conf.CheckPKGConfig( 'QtCore', "4.2", True )
conf.CheckPKGConfig( 'QtGui', "4.2" )
conf.CheckPKGConfig( 'QtNetwork', "4.2", True )

env = conf.Finish()

env['PREFIX'] = ARGUMENTS.get('PREFIX', '/usr/local')

if not env.has_key('PREFIX'):
	print """\
No Prefix set! Will assume /usr/local. To change it use 'scons PREFIX=<path>'
Note that <ou have to use this everytime as it is not cached currently.
"""
	env['PREFIX'] = '/usr/local'

env['PREFIX_BIN'] = env['PREFIX'] + "/bin"
env['PREFIX_LIB'] = env['PREFIX'] + "/lib"
env['PREFIX_INC'] = env['PREFIX'] + "/include/ofqf"

env.Alias( 'install', env['PREFIX_BIN'] )
env.Alias( 'install', env['PREFIX_LIB'] )
env.Alias( 'install', env['PREFIX_INC'] )

from SCons.Util import *

# Commands for the qt support ...
# command to generate header, implementation and moc-file
# from a .ui file
# taken from /usr/lib/scons-0.96.94/SCons/Tool/qt.py
env['QT_UICCOM'] = [
	CLVar('$QT_UIC $QT_UICDECLFLAGS -o ${TARGETS[0]} $SOURCE'),
	CLVar('touch ${TARGETS[1]} ') ,
	CLVar('touch ${TARGETS[2]}') ]

## target processing is done in the subdirectory
env.SConscript( dirs=['libofqf','oscqlient','oscserver'], exports="env" )

pkgconfig = env.ScanReplace('ofqf.pc.in')
env.Install( env['PREFIX_LIB'] + '/pkgconfig', pkgconfig )

