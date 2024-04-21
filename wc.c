///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 6 - Readelf - SRE - Spring 2024
//
/// readelf - reads executable files to display the headers, section headers, sybol tables, etc.
///
/// @see     https://github.com/Trusted-Execution/.github/blob/main/documentation/elf.pdf
///
/// @file    readelf.c
/// @author  Kobe Uyeda <kobek@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>     // For printf()
#include <stdlib.h>    // For exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <sys/stat.h>  // For stat()


/// The main entry point for wc
///
///   - Process command line parameters
///   - Orchistrate the file management
///   - Call a dedicated function to process files
int main( int argc, char* argv[] ) {

   
	
   close( fd );
	/// @todo Check the exit status

   exit( EXIT_SUCCESS );
}
