#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>

#include "defs.h"

string *path_arr = ({}),
        nickname;

public void
create_monster()
{
    int     rnd1 = random(11),
            rnd2 = random(11);

    set_race_name("human");
    default_config_npc(15);
    set_stats(({ 18 + rnd1, 15 + rnd2, 15,
                 15 + 2 * rnd1 - rnd2, 15 - rnd1 + 2*rnd2, 15 + (rnd1+rnd2)/2, }));
}

public void
set_path(string p)
{
    path_arr = explode(p, " ");
}

public void
set_nickname(string n)
{
    nickname = n;
    add_name(n);
}

public void
set_con(int l)
{
    set_base_stat(SS_CON, l*5+15);
}

public void
start_walking()
{
    stats_to_acc_exp();
    seq_new("go_to_pub");

    seq_addfirst("go_to_pub",
      ({"@@delay|1|0",		"bow",			"@@delay|1|0",
        "grin"
      })
      + path_arr +
      ({"say Hi guys! Here I am.",
        "@@delay|1|0",		"smile",		"introduce myself"
      })
    );
}

varargs public string
delay(string arg1, string arg2)
{
    int a,b,c;

    if (strlen(arg1))
        sscanf(arg1,"%d",a);
    else
        a = 1;

    if (strlen(arg2))
        sscanf(arg2,"%d",b);
    else
        b = 1;

    c = random(a)+b;

    return ("" + c + "");
}

public void
arm_me()
{
    string  wep,
           *wep_arr = ({S_LOCAL_WEP_DIR + "bbottle",
                        S_COMMON_WEP_DIR + "dagger",
                        S_COMMON_WEP_DIR + "knife",
                        S_LOCAL_WEP_DIR + "axe",
                        S_LOCAL_WEP_DIR + "ssword",
                        S_LOCAL_WEP_DIR + "lsword",
                        S_LOCAL_WEP_DIR + "rapier" });

    seteuid(getuid(this_object()));

    wep = one_of_list(wep_arr);

    clone_object(wep)->move(TO);
    command("wield all");
}

