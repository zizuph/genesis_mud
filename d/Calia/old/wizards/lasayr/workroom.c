inherit "/std/workroom";

#include <stdproperties.h>
#include "../domain.h"
#pragma save_binary


create_workroom()
{

  object door;
  
  set_short("A cavernous hall");
  set_long("You are lessened by the imensity " +
  " of the cavernous hall you now stand in. " +
  "Seemingly natural, the cavern extends itself " +
  "evenly around and raises as high as the eye " +
  "can see. A quick view of the entirety lends " +
  "you belief that you stand in an antechamber " +
  "of sorts. With a singular sign of use by way " +
  "of a podium in the very center of this hall. " +
  "It seems less used and less likely travelled, " +
  "yet oddly you feel watched. Several large " +
  "stone doors hold this room with an enormous " +
  "half-built archway placed in the northern " +
  "preface of the cavern. A low rumble is felt " +
  "beneath your feet.\n");

  add_item(({"wall","walls"}),"Walking the edge " +
  "of the cavern, you take care to notice that the " +
  "walls are not so natural. The rock has been " +
  "hewed away with force rather than skill, leaving " +
  "uneven gaps of shadow.\n");

  add_item("floor","A low rumble emanates from the " +
  "ground you stand on. Lacking any semblance of " +
  "rhythm, it seems to numb you. The floor distantly " +
  "begins to waver in sync.\n");

  add_item("podium","On a slightly elevated position " +
  "in the center of the cavern, the singular item that " +
  "shows its use. A podium lifted from the floor, held " +
  "in the air with perfect poise.\n");

  add_item(({"arch","archway","preface"}),"Not entirely " +
  "constructed as of yet, the little of the archway you " +
  "do make out seems to be made of bones. Rather contorted " +
  "they make an intricate latice only reaching a hand " +
  "reach high at the moment. The shadows seem to linger " +
  "in this part of the cavern.\n");

  add_item(({"bone","bones"}),"Mishapen and bent beyond " +
  "recognition, only by might of magic would something take " +
  "this form. Vaguely you can still make out the skull of a " +
  "humanoid, or another piece that hasn't been tainted. They " +
  "seem brittle and cold to the touch.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_HIDE,90);

  add_exit("/d/Calia/common/domain_entr", "south", 0);

  door = clone_object("/d/Calia/lasayr/w_door1");
  door->move(this_object());

  door = clone_object("/d/Calia/lasayr/e_door2");
  door->move(this_object());

}

int
query_prevent_snoop()
{
    return 1;
}
