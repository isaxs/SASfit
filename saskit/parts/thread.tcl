# part: thread {{{
part::create thread \
    -buildcommand {
        conf::norelnoacmainconfigure [part::srcdir thread] --disable-shared [conf::c_with tcl] [conf::c_disen debug symbols]
	if {$::tcl_platform(platform) == "windows"} {
	    out::printcommand "Converting Makefile"
            utils::withfile [file join [part::destdir thread] Makefile] fc {
    	        regsub -all -line "(EXTRA_CFLAGS.*?=.*?) -YX" $fc "\\1" fc
    	        regsub -all -line "^CFLAGS_OPTIMIZE.*?=.*\$" $fc "CFLAGS_OPTIMIZE = -O2" fc
	        regsub -all -line "CFLAGS_DEBUG.*?=.*\$" $fc "CFLAGS_DEBUG = -g" fc
	        regsub -all -line "^\\*\\.lib" $fc "*.a" fc
	        regsub -all -line "(LIB_FILE.*?=.*?).lib" $fc "\\1.a" fc
	        regsub -all -line "^STLIB_LD.*?=.*?lib.*\$" $fc "STLIB_LD = ar cr" fc
            }
	}
        conf::make binaries
    } \
    -initcommand {
        return "Tcl_StaticPackage(0, \"Thread\", Thread_Init, Thread_SafeInit);\n"
    } \
    -externcommand {
        return "Tcl_AppInitProc Thread_Init, Thread_SafeInit;\n"
    } \
    -definescommand {
    } \
    -librarycommand {
        upvar c c
        set dir [part::srcdir thread]
        set ver [part::srcversion $dir]
        return [list [part::destdir thread]/[conf::libname thread $ver end 0]]
    } \
    -kitpatterns {lib/thread@VER@} \
    -depend {tcl} \
    -options {debug 0}
# }}}

