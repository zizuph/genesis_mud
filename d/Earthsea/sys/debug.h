/* using this file:
 * 1) if you wish to statically define the object which will be receiving
 *    debug messages (this_player(), for instance), add the line
 *    #define DEBUG_WHO this_player()
 * 2) if you wish to have multi-level debugging, set the current debug-level
 *    by adding the line
 *    #define DEBUG_LEVEL 1
 *    The above sets the debug level to 1.  DEBUG_LEVEL should be an integer
 *    corresponding to a bit map indicating which levels of debugging
 *    should be printed. I.e. 
 *      DEBUG_LEVEL 1  results in only level 1 messages being printed
 *      DEBUG_LEVEL 2  results in only level 2 messages being printed
 *      DEBUG_LEVEL 3  results in level 1 and 2 messages being printed
 * 3) add the line
 *    #define DEBUG_ON
 *    This enables the debugging messages.  To disable, #undef DEBUG_ON or
 *    remove the #define DEBUG_ON line
 * 4) #include this file.
 *
 * debug messages are printed using the DEBUG macro; it may have different
 * arguments depending on what you defined above.
 *
 * If DEBUG_LEVEL was defined, then the first argument must be an integer.
 * The integer corresponds to the binary value of the debugging level at 
 * which the message should be printed (see the DEBUG_LEVEL description above).
 * For instance, a message that should be printed at level 1 debugging should
 * be given a debugging-level argument of 1 (bin 001), a message to be printed 
 * at level 2 an argument of 2 (bin 010), and a message to be printed at level 
 * 3 an argument of 4 (bin 100).
 *
 * If DEBUG_WHO was NOT defined, the object to receive the message will have
 * to be specified.  This is the first agument if DEBUG_LEVEL is not defined
 * or the second argument if DEBUG_LEVEL is defined.
 *
 * The last argument is always the string to print as a debug message.
 *
 * some examples:
 * _______________________________________________________________________
 * #define DEBUG_LEVEL 3
 * #define DEBUG_WHO  this_interactive()
 * #define DEBUG_ON
 * #include "/d/Domain/sys/debug.h"
 *
 * void some_func()
 * {
 *   ...some code...
 *   DEBUG(1, "This message will be printed at DEBUG_LEVEL 3");
 *   ...some code...
 *   DEBUG(2, "This message will be printed at DEBUG_LEVEL 3");
 *   DEBUG(4, "This message will not be printed at DEBUG_LEVEL 3");
 * }
 * _______________________________________________________________________
 * #define DEBUG_WHO this_player()
 * #define DEBUG_ON
 * #include "/d/Domain/sys/debug.h"
 *
 * void some_func()
 * {
 *   ...some code...
 *   DEBUG("This message will be printed to this_player().");
 * }
 *________________________________________________________________________
 * #define DEBUG_ON
 * #include "/d/Domain/sys/debug.h"
 *
 * void some_func()
 * {
 *   ...some code...
 *   DEBUG(this_player(), "This message will go to this_player().");
 *   ...some code...
 *   DEBUG(this_interactive(), "This message will go to this_interactive().");
 * }
 * 
 * Questions?  Comments?  Mail Shiva.
 */

#ifdef  DEBUG_ON
#define DUMP_ARR(arr) dump_array(arr)
#define DUMP_MAP(m)   dump_mapping(m)
#else
#define DUMP_ARR(arr)
#define DUMP_MAP(m)
#endif  DEBUG_ON

#ifdef  DEBUG_LEVEL

#ifdef  DEBUG_WHO

#ifdef  DEBUG_ON
#define DEBUG(x, y)    if ((DEBUG_LEVEL) & (x)) \
                       tell_object(DEBUG_WHO, y + "\n")
#else   //DEBUG_ON
#define DEBUG(x, y)
#endif  DEBUG_ON

#else   //DEBUG_WHO

#ifdef  DEBUG_ON  
#define DEBUG(x, y, z) if ((DEBUG_LEVEL) & (x)) \
                               tell_object(y, z + "\n")
#else   //DEBUG_ON
#define DEBUG(x, y, z)
#endif  DEBUG_ON

#endif  DEBUG_WHO

#else   //DEBUG_LEVEL

#ifdef  DEBUG_WHO

#ifdef  DEBUG_ON
#define DEBUG(x)       tell_object(DEBUG_WHO, x + "\n")
#else   //DEBUG_ON
#define DEBUG(x)
#endif  DEBUG_ON

#else   //DEBUG_WHO

#ifdef  DEBUG_ON
#define DEBUG(x, y)    tell_object(x, y + "\n")
#else   //DEBUG_ON
#define DEBUG(x, y)
#endif  DEBUG_ON

#endif  DEBUG_WHO

#endif  DEBUG_LEVEL



