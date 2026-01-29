/* A mortar used to mix potions or grind herbs
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 2/8/98      Zima        Created
**
*/
inherit "/d/Genesis/std/potions/mortar";
 
void create_container() {
   ::create_container();
   add_adj(({"ceramic","white","grinding"}));
   set_short("ceramic mortar");
   set_long("It is a ceramic white mortar, a small thick-walled bowl used "+
            "to mix potions and, with a pestle, grind herbs into powders.\n");
 
}

public string query_auto_load() { return 0; } // do not autoload
