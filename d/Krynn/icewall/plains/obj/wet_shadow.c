/* Created by Macker 09/14/94 */

/* (Actually I sorta copied it from a Shire file
	but I won't tell if you don't ;) */

/*Actually I had permission to do it ;) */

/* Well I did personally alter one line =) */
inherit "/std/shadow";

varargs public mixed
query_adj(int arg) 
{
    return ({"rather", "wet"});
}
 
int 
query_wet_shadow()
{
    return 666;
}

void
destruct_wet_shadow()
{
    set_alarm(1000.0,0.0,"remove_shadow");
}

void
remove_wet_shadow()
{
    remove_shadow();
}
