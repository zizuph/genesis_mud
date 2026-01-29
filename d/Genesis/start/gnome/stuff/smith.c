#include "stdproperties.h"
#include "../gnome.h"

#pragma save_binary

inherit  MERCHANT;

create_merchant() {
    set_name("blackblade");
    default_config_npc(23);
    seq_new("foo"); seq_addfirst("foo", ({ "@@makemoney" }) );
}

void
makemoney() {
  seteuid(getuid());
  transact(3000, 0, this_object(), 1);
}
status
accept_object(object ob) {
    return ob->id("weapon");
}

int maximum_wealth() { return 1000; }