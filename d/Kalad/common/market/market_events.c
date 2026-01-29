/* by Ashbless - pick pockets of players in market */

inherit "/std/object";

#include "/d/Kalad/defs.h"


pick_pockets()
{

    int n;
    object *player;

    player = users();
    while(n < sizeof(player))
    {
      if (query_in_market(player[n]) && !E(player[n])->query_prop(MRKT_IN_NO_HEAR))
    if ( !(E(player[n])->query_prop(ROOM_I_INSIDE)) )
      tell_object(player[n],
        "You think you feel a slight pulling at your belt pouch\n"+
        "as you push through the crowd, but when you turn there\n"+
        "is no clue as to the culprit. You quickly check your " +
        "possessions.\n");
    else
      tell_object(player[n],
      "From outside you hear someone yell, 'Stop Thief!'\n");

      n = n + 1;
    }

    call_out("pick_pockets", (10 * random(18)) + 10);

}


query_in_market(object player)
{

    string roomstr, s1, s2;

    if( !E(player) || !file_name(E(player)) )
      return 0;

    roomstr = file_name(E(player));

    if (sscanf(roomstr,"%sKalad/common/market%s",s1,s2) == 2)
      return 1;
    else return 0;

}


start_events()
{

    call_out("pick_pockets",30);

}
