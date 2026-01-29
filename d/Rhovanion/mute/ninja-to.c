inherit "/std/weapon";
#include "/sys/wa_types.h"
void
create_weapon()
{
set_name("ninjasword");
set_short("hyper-combat ninjasword");
set_long("This sword appears to be the ultimate in Hyper-ninja combat technology"+
"It's razor sharp blade bear the letters N  I  N  J  A  along its length.  It's"+
"handle is covered in black leather and an orange streamer extends"+
"from the pommel.  The hilt of this mean weapon is a ninja throwing star! \n");
set_adj("hyper-combat");
set_hit(60);
set_pen(60);
set_wt(W_SWORD);
set_dt(W_SLASH | W_IMPALE);
set_hands(W_ANYH);
}
