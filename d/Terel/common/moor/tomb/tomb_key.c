/*
    Modified: 6 May 2003, by Bleys
        - Changed one of the adjectives from 'iron' to 'stone'

    Modified: 10 Sep 2003, by Bleys
        - Made the key keepable

    Modified: 11 Sep 2003, by Bleys
        - Whoops. I made the key recoverable, too, which was
            unintended. Fixed now.


*/

inherit "/std/key";
inherit "/lib/keep";

create_key()
{
     ::create_key();

     set_short("stone key");
     set_adj(({"stone", "heavy"}));
     set_long("It's a heavy key. It's made from stone.\n");
     set_name("tomb key");
     add_name("key");
	 add_adj("tomb");
     set_key(3141592);

}
