#include <stdio.h>
#include <signal.h>
#include <execinfo.h> 
#include <cxxabi.h>
#include "stack_tracer.h"

StackTracer::StackTracer()
{
	int signals[] = {SIGABRT, SIGSEGV, SIGILL, SIGFPE};
	int count = sizeof(signals) / sizeof(signals[0]);

	for(int i = 0; i < count; ++i)
	{
		signal( signals[i], SignalHandler );		
	}
}

void StackTracer::SignalHandler( int signum )
{
   const char* name = NULL;
   switch( signum )
   {
   case SIGABRT: name = "SIGABRT";  break;
   case SIGSEGV: name = "SIGSEGV";  break;
   case SIGBUS:  name = "SIGBUS";   break;
   case SIGILL:  name = "SIGILL";   break;
   case SIGFPE:  name = "SIGFPE";   break;
   }
 
   if ( name )
      printf( stderr, "Caught signal %d (%s)\n", signum, name );
   else
      printf( stderr, "Caught signal %d\n", signum );
    
   PrintStackTrace();

   exit( signum );
}

void StackTracer::PrintStackTrace()
{
   printf("stack trace:\n");
 
   // storage array for stack trace address data
   int max_frames = 63;
   void* addrlist[max_frames+1];
 
   // retrieve current stack addresses
   unsigned int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));
 
   if ( addrlen == 0 ) 
   {
      printf( "  \n" );
      return;
   }
 
   // resolve addresses into strings containing "filename(function+address)",
   // Actually it will be ## program address function + offset
   // this array must be free()-ed
   char** symbollist = backtrace_symbols( addrlist, addrlen );
 
   size_t funcnamesize = 1024;
   char funcname[1024];
 
   // iterate over the returned symbol lines. skip the first, it is the
   // address of this function.
   for ( unsigned int i = 4; i < addrlen; i++ )
   {
      char* begin_name   = NULL;
      char* begin_offset = NULL;
      char* end_offset   = NULL;
 
      // find parentheses and +address offset surrounding the mangled name
      // ./module(function+0x15c) [0x8048a6d]
      for ( char *p = symbollist[i]; *p; ++p )
      {
         if ( *p == '(' )
            begin_name = p;
         else if ( *p == '+' )
            begin_offset = p;
         else if ( *p == ')' && ( begin_offset || begin_name ))
            end_offset = p;
      }
 
      if ( begin_name && begin_offset && end_offset && ( begin_name <  begin_offset ))
      {
         *begin_name++   = '\0';
         *end_offset++   = '\0';
         if ( begin_offset )
            *begin_offset++ = '\0';
 
         // mangled name is now in [begin_name, begin_offset) and caller
         // offset in [begin_offset, end_offset). now apply
         // __cxa_demangle():
 
         int status = 0;
         char* ret = abi::__cxa_demangle( begin_name, funcname,
                                          &funcnamesize, &status );
         char* fname = begin_name;
         if ( status == 0 ) 
            fname = ret;
 
         if ( begin_offset )
         {
            printf( "  %-30s ( %-40s  + %-6s) %s\n",
                     symbollist[i], fname, begin_offset, end_offset );
         } 
         else 
         {
            printf( "  %-30s ( %-40s    %-6s) %s\n",
                     symbollist[i], fname, "", end_offset );
         }

      } 
      else 
      {
         // couldn't parse the line? print the whole line.
         printf("  %-40s\n", symbollist[i]);
      }
   }
 
   free(symbollist);
}






















class KxStackTrace
{
public:
    KxStackTrace();
};


#include "stack_tracer.h"

int main(int argc, char* argv[])
{
	KxStackTrace tracer;
	return 0;
}