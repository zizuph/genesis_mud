/* created by Aridor, 03/10/94 */

#include "../local.h"
inherit THEIWAR_BASE
#include <macros.h>
#include <money.h>

void
create_theiwar()
{
    set_adj("scared");
}


void
arm_me()
{
  seteuid(getuid(TO));
  MONEY_MAKE(random(1),"gold")->move(TO);
  clone_object(OBJ + "miniaxe")->move(TO);

  command("wield all");
}
