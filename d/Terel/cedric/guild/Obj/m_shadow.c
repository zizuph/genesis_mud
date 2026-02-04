inherit "/std/shadow";

/*
 * Lots of players have an obsolete minstrel shadow in their path called
 * /guild/obj/m_shadow. This is a dummy version of that file that does
 * nothing but remove itself, thus cleaning those annoying error messages
 * out of the lplog
 * 
 * Modified by Mortricia 960503. Since shadow_who is set in the normal
 * call to autoload_shadow() we cannot use it without calling the
 * previous autoload_shadow(). Also added the log.
 */

/*
void autoload_shadow(string str)
{
    seteuid(getuid(this_object()));
    query_shadow_who()->remove_autoshadow(this_object());
}
*/

#define LOG   "/d/Terel/cedric/guild/obj/shadow.log"

public void
autoload_shadow(mixed arg)
{
    int suc;
    
    ::autoload_shadow(arg);  /* Now we can use query_shadow_who() */
    
    if (query_shadow_who()) {
        suc = query_shadow_who()->remove_autoshadow(this_object());
        seteuid(getuid());
        write_file(LOG, "Removed (" + suc + ") obj/m_shadow.c from " +
                        query_shadow_who()->query_real_name() +
                        " (" + ctime(time()) + ").\n");
    }
    
    remove_shadow();         /* Let's also remove this shadow */
}
