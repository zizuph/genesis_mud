/*
*    unlocks the door to Master Theobald's residence
*/
inherit "/std/key";
inherit "/lib/keep";

void
create_key() 
{
   ::create_key();
   set_name("key");
   set_short("elaborate key");
   set_pshort("elaborate keys");
   set_adj("elaborate");
   set_long("This elaborate key unlocks the door to Master Theobald's " +
       "private residence.\n");   
   set_key(8874653);
}
