/*
 * Ingredient for the PHARM spell.
 * It must be blessed to be able to be used.
 */
 
#include <stdproperties.h>
#include <macros.h>
 
inherit "/std/object";

int gBlessed = 0;
 
void
create_item()
{
    set_short("silver charm");
    set_pshort("silver charms");
 
    set_long("This is a small circular silver charm about " +
        "half an inch in diametre. On one side a dragon " +
        "talon is depicted in relief. @@check_blessed@@");
 
}
 
string
check_blessed()
{
  if(gBlessed)
    return "The other side is carved with a fine " +
           "straight line across.\n";
  else
    return "The other side is totally smooth.\n";
}
 
void
bless_charm()
{
  gBlessed = 1; 
}
 
int
query_blessed()
{
  return gBlessed;
}
 
/*
 * Function name: query_recover
 * Description  : Called to check whether this weapon is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the weapon recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your weapon to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + "|:|" + gBlessed + "|:|";
}
 
/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called
 *                to set the necessary variables. If you redefine the
 *                function, you must add a call to init_wep_recover
 *                with the string that you got after querying
 *                query_wep_recover.
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    int value;
    string foobar;
   
    sscanf(arg, "%s|:|%d|:|%s", foobar, value, foobar);
 
    gBlessed = value;
}
