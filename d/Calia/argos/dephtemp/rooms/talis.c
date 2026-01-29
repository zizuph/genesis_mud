/*
**  Temple of Dephonia - Chamber of the Priestess of the Talisman
**
**  Early in the history of the Order, the goddess Dephonia gave a Talisman
**  to her persecuted followers who lived in secret amongst the people of
**  the city of Tritheonopolis (Argos) at the time. This Talisman allows
**  a Dephonian priest/priestess to poison food and drink.
**
**  This chamber is set aside as the place where the current priestess
**  (monsters/talisprs)
**  in charge of the talisman does her work, but she will only poison
**  the sacramental wine (objects/sacwine) found in the winery (rooms/
**  winery) for an infidel (a player, non-member of the order). This
**  blessing is required to do the vision quest.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
 
object priestess=0;
 
/* prototype */
void do_bless(mixed parms);

void
reset_room()
{
    if (priestess) return;
    priestess=clone_object(NPC_DIR+"talisprs");
    priestess->equip_me();
    priestess->move(THIS);
    tell_room(THIS, QCTNAME(priestess)+" rises from meditation.\n");
}
 
create_room() {
   set_short("A Chamber in the Temple of Dephonia");
   set_long(
      "Your eyes begin to water from the steam which rises from "+
      "a large iron vessel that is suspended from a tripod over "+
      "a small pit of fire in the center of this rectangular "+
      "chamber. "+
      "A large mural covers the long southeastern wall, while "+
      "two identical banners hang on the walls at the ends of "+
      "the chamber. You feel you should leave soon before the "+
      "fumes overcome you.\n");
 
   add_item("steam","It is a green steam which rises from the "+
                    "iron vessel.\n");
   add_item(({"vessel","pot"}), "It is a large iron pot made in the "+
              "shape of a globe. It is suspended above a small pit "+
              "of fire by a tripod.\n");
   add_item("tripod","Three long iron rods joined at their ends "+
            "used to suspend the vessel over the fire.\n");
   add_item(({"fire","pit"}),
              "There is a small circular pit in the center of "+
              "the chamber with a small fire used to heat the "+
              "iron vessel suspended over it.\n");
   add_item("mural",
            "It is a painting which covers the entire southeastern "+
            "wall. It depicts a nobleman who is falling backwards "+
            "in a chair before a table set with a feast, his eyes "+
            "bulging in horror. What looks like a servant girl "+
            "stands nearby holding a bottle of wine, wearing a "+
            "talisman around her neck, a devious smile on her face.\n");
   add_item(({"banner","banners"}),
            "Two identical banners hang on the walls on either end "+
            "of the chamber, made of black silk bearing the symbol "+
            "of a talisman with a coiling snake encircled by a "+
            "wreath of hemlock leaves.\n");
 
   add_item(({"for blessing","for a blessing"}), "What?\n");
   add_cmd_item(({"for blessing","for a blessing"}), "pray","@@bless");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"corr15","west",0);
   reset_room();
}
 
int bless() {
   object TPlay=this_player();
   object wine=present(VDQ_WINE,TPlay);
 
   if (priestess) {
      if (wine) {
         set_alarm(1.0,0.0, &do_bless(({TPlay,1})));
         }
      else
         priestess->command("say I will bless nothing you have, infidel.");
   }
   else
   write("You pray for a blessing, but there is no one to hear it.\n");
 
   return 1;
}
 
void do_bless(mixed parms) {
    int    step;
    object TPlay;
    object TRoom=this_object();
    object wine;
 
    if (sizeof(parms) != 2) return;
    TPlay = parms[0];
    step  = parms[1];
    set_this_player(TPlay);
 
    switch (step) {
        case 1:
            if (!present(TPlay, TRoom)) return;
            priestess->command("emote raises her hands above her head.");
            break;
        case 2:
            if (!present(TPlay, TRoom)) return;
            priestess->command("emote shouts Praised be the Light of "+
                               "Darkness and Our Mother who brings it!");
            break;
        case 3:
            if (!present(TPlay, TRoom)) return;
            priestess->command("emote chants: Send thy blessing upon "+
                              "this infidel who honours you, Our Mother!");
            break;
        case 4:
            if (!present(TPlay, TRoom)) return;
            tell_room(TRoom, "The talisman around the "+
                             "priestess' neck begins to glow!\n");
            break;
        case 5:
            if (!present(TPlay, TRoom)) return;
            priestess->command("say Receive the blessing of the Talisman!");
            priestess->command("emote lowers her head and closes her eyes.");
            break;
        case 6:
            if (!present(TPlay, TRoom)) return;
            priestess->command("emote looks at you and smiles deviously.");
            wine=present(VDQ_WINE,TPlay);
            if (wine) wine->add_prop(VDQ_POISONED,1);
            return; /* needed at last step */
            break;
        default:
            write("You notice something wrong in the fabric of space.\n");
            log_file("bugs","Invalid step num in talis.c.\n");
            return;
    }
    set_alarm(5.0, 0.0, &do_bless(({TPlay,(step+1)})));
}

