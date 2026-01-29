/*
 * WARNING: This is OBSOLETE. Do not use!
 * Use standard recover routines instead. If you insist on using it
 * never use it on items which have a query_recover defined already.
 * 
 * - Cotillion, 2019-05-01
 * 
 * WARNING WARNING WARNING 
 * 
 * 
 * WARNING WARNING WARNING
 * 
 * This is an include that can be used for standard objects that, by default,
 * should be recoverable. Notice that it only works for objects that aren't
 * modified after they have been cloned. It that case you must store the
 * modified parts (special properties etc.) through an own-written
 * query_recover() and init_recover(string arg).
 *
 * See ~mortricia/camp/q_ring.c for an example of this.
 *
 * Modified: Bleys 28 Apr 2003
 *    - added query_keep_recover() to query_recover()
 *    - added init_keep_recover(arg) to init_recover()
 *    - these so that recoverable Terel items will remember their
 *        "keep" status over reboots and logouts.
 *
 * Modified: 18 Sep 2003, by Bleys
 *    - The previous implementation assumed that /lib/keep.c was inherited,
 *        which, in retrospect, is a bogus assumption. Now it tests for
 *        the presence of the query_keepable function.
 *
 */

string
query_recover()
{
    string recover_str;

    recover_str = explode(file_name(this_object()) + "#", "#")[0] + ":";


    // This attempts to salvage this disaster include for weapons and armours 
    string *functions = ({ 
            "query_keep_recover", 
            "query_wep_recover", 
            "query_arm_recover"
            });

    foreach (string fun: functions) 
    {
        if (function_exists(fun, this_object()))
        {
            recover_str += call_other(this_object(), fun);
        }
    }

    return recover_str;

}

void
init_recover(string arg)
{
    // Doesn't matter if they're not defined
    TO->init_wep_recover(arg);
    TO->init_arm_recover(arg);
    TO->init_keep_recover(arg);
}
