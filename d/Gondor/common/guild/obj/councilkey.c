/*
 * Gwyneth Nov. 4, 2000 - Removed Elessar's name from who_gives()
 *                        and replaced it with a Gondor domain wizard
 *                        query.
*/
#pragma save_binary

inherit "/std/key";
#include <stdproperties.h>
#define COUNCIL "/d/Gondor/common/guild/council"

void test_council_member(object player);

create_key()
{
  ::create_key();
  add_name("_council_key");
  set_adj("golden");
  set_pshort("golden keys");
  set_long("This is the key to the council-room of the Council of Rangers.\n"+
    "Only the members of the Council are allowed to carry this key.\n");
  set_key("council_key");
  add_prop(OBJ_I_NO_DROP,"@@who_gives");
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_WEIGHT,10);
  add_prop(OBJ_I_VALUE,0);
}

init()
#include <files.h>
{
    set_alarm(10.0, 0.0, &test_council_member(this_player()));
}

void
test_council_member(object player)
{
  if (player != environment(this_object())) return;
  if (!player) remove_object();
  if (player->query_wiz_level()) return;
  seteuid(getuid(this_object()));
  COUNCIL->short();
  if (!COUNCIL->is_officer(player->query_real_name())) {
  write("You are not allowed to have this key!\n");
    write("The key melts out of your hand.\n");
    remove_object();
    return;
    }
  return;
}
/*
Removing auto load after new guild recode.
query_auto_load()
{
  return "/d/Gondor/common/guild/obj/councilkey:";
}
*/
who_gives()
{
    if (SECURITY->query_wiz_dom(this_player()->query_real_name()) == "Gondor")
        return 0;
  return 1;
}

string query_recover() { return 0; }
