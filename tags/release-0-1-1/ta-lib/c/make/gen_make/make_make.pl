#!/usr/bin/perl

# You should not have to call this script directly. Use instead
# the "gen_make.pl" who effectively do everything.

# This script will create all the makefiles for all
# the plateform using the projects describe in the
# '/c/make/gen_make' directory.
#
# This script is called with a parameter defining the
# type of application with which the library is link:
# Example:
#    'perl make_make.pl cmr ...' creates the console/multithread/release makefiles.
#    'perl make_make.pl cmd ...' creates the console/multithread/debug makefiles.
#

use File::Path;
use File::DosGlob 'glob';
use Env;

if( (scalar @ARGV) != 4 )
{
   print( "Missing parameter\n" );
   print( "Usage: make_make <cmr|cmd|csr|csd|cdr|cdd> TMAKEPATH destPath platform\n" );
   print( "\n" );
   print( "       platform = {all|linux_only|msvc_only}\n" );
   die;
}

if( @ARGV[0] eq "cmr" ) {
   $makeConsole = 1;
   $makeThread = 1;
   $makeDebug = 0;
   $makeDLL = 0;
}
elsif( @ARGV[0] eq "cmd" ) {
   $makeConsole = 1;
   $makeThread = 1;
   $makeDebug = 1;
   $makeDLL = 0;
}
elsif( @ARGV[0] eq "csr" ) {
   $makeConsole = 1;
   $makeThread = 0;
   $makeDebug = 0;
   $makeDLL = 0;
}
elsif( @ARGV[0] eq "csd" ) {
   $makeConsole = 1;
   $makeThread = 0;
   $makeDebug = 1;
   $makeDLL = 0;
}
elsif( @ARGV[0] eq "cdr" ) {
   $makeConsole = 1;
   $makeThread = 1;
   $makeDebug = 0;
   $makeDLL = 1;
}
elsif( @ARGV[0] eq "cdd" ) {
   $makeConsole = 1;
   $makeThread = 1;
   $makeDebug = 1;
   $makeDLL = 1;
}
else
{
   print( "Bad parameter\n" );
   die;
}

$origTMAKEPATH = @ARGV[1];
$ENV{'TMAKEPATH'} = $origTMAKEPATH;

# print "MAKEPATH[".$origTMAKEPATH."]\n";

$origTemplatePath = @ARGV[2];
@platformCompilerPath = glob $origTemplatePath;

# print "Template Path[$origTemplatePath]\n";
# print "Platform-Compiler Path[@platformCompilerPath]\n";
print "Generating (".@ARGV[0].") ";

if( $makeConsole == 1 ) {
   print "CONSOLE ";
}
else {
   print "WINDOWS ";
}

if( $makeThread == 1 ) {
   print "MULTITHREAD ";
}
else {
   print "SINGLE-THREAD ";
}

if( $makeDLL == 1 )
{
   print "DLL ";
}

if( $makeDebug == 1 ) {
   print "DEBUG ";
}
else {
   print "RELEASE ";
}
   
print "makefiles...\n";


# Clean-up existing platform/compiler directory.

# Note:
#foreach $z (@platformCompilerPath) {
   # Get the last element of each path. This
   # is the platformcompiler string.
#   @splitPath = split( /[\\\/]/, $z );
#   $platformCompiler = @splitPath[$#splitPath];
   
#   ($platform,$compiler) = split( /-/, $platformCompiler );

   # Skip the cases causing trouble.
#   next if( length($platform) == 0 );
#   next if( length($compiler) == 0 );

   # Clean-up the directories
#   rmtree( "../".@ARGV[0]."/".$platform );
#}

# For each platform/compiler pair, create the directory structure.
foreach $z (@platformCompilerPath) {

   # Get the last element of each path. This
   # is the platformcompiler string.
   @splitPath = split( /[\\\/]/, $z );
   $platformCompiler = @splitPath[$#splitPath];

   ($platform,$compiler) = split( /-/, $platformCompiler );
   
   # Skip the cases causing trouble.
   next if length($platform) == 0;
   next if length($compiler) == 0;

   # On non win32 platform, skip generating the win32 makefiles.
   if( $^O ne "MSWin32" )
   {   
      next if ($platform eq "win32");
   }
   
   if( @ARGV[3] eq "linux_only" )
   {
      next if($platform eq "win32");
      next if($platform eq "cygwin" );
   }

   if( @ARGV[3] eq "msvc_only" )
   {
      next if($compiler ne "msvc");
   }

   # cdr and cdb are generated with msvc only
   if( $compiler ne "msvc" )
   {
      next if($makeDLL eq 1);
   }

   # Create the directories
   $dirToProcess = "../".@ARGV[0]."/".$platform."/".$compiler;
   print "Doing ".$platform."-".$compiler."... ";
   mkpath( $dirToProcess );

   # For each .pro file in the ta-lib/c/make/tmake,
   # duplicate the same directory structure and
   # execute tmake.
   @proList = glob "*/*.pro";

   foreach $y (@proList) {
      ($proPath, $proFile) = split( /[\\\/]/, $y );

      mkpath( $dirToProcess."/".$proPath );
      if ($platform ne "win32")
      {
         $toRun = "tmake -unix"; 
      }
      else
      {
         $toRun = "tmake -win32"; 
      }

      if( $makeDebug == 1 ) {
         $toRun = $toRun." "."\"CONFIG+=debug\"";
      }
      else {
         $toRun = $toRun." "."\"CONFIG+=release\"";
      }

      if( $makeConsole == 1 ) {
         $toRun = $toRun." "."\"CONFIG+=console\"";
      }
      else {
         $toRun = $toRun." "."\"CONFIG+=windows\"";
      }

      if( $makeThread == 1 ) {
         $toRun = $toRun." "."\"CONFIG+=thread\"";
      }

      if( $makeDLL == 1 ) {
         $toRun = $toRun." "."\"CONFIG+=thread\"";
      }

      $toRun = $toRun." "."\"CONFIG+=".@ARGV[0]."\"";
     
      $toRun = $toRun." ".$proPath."/".$proFile;
      $toRun = $toRun." -o "."../".@ARGV[0]."/".$platform."/".$compiler."/".$proPath."/"."Makefile";
      $ENV{'TMAKEPATH'} = $origTMAKEPATH."\\..\\".$platformCompiler;
      system $toRun;
   }

   # Create the root Makefile.
   $toRun = "tmake";
   $toRun = $toRun." "."\"TMAKEPATH=".$origTMAKEPATH."/../".$platformCompiler."\"";
   $toRun = $toRun." rootmake.pro";
   $toRun = $toRun." -o "."../".@ARGV[0]."/".$platform."/".$compiler."/Makefile";
   # print "to run = $toRun\n";
   system $toRun;

   print "done."."\n";
}

