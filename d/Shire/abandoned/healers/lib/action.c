/*
 * Combat action telling routines. 
 *
 * This file parses a TELLEM style string into a piece of code. 
 * The syntax is: 
 *
 * <designator> ::= $   /* First argument, usually the S-object. */
 *                | #   /* Second argument, usually the O-object. */
 *  
 *

 Example:
 
 parse_tellem("$You $aim for #'s %2, but $miss.", me, you, "head")

 Note that $ is short for %0, # is short for %1.

 me->catch_msg("You aim for " + you->query_possessive(me) + " head, but misses.");
 you->catch_msg(me->query_The_name() + " aims for your head, but misses.");
 me->tell_watcher(QCTNAME(me) + " aims for " + HIS_HER(you) + " head, but misses.");


int parse_tellem(string format)
{
    
