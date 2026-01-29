/*
** This causes a player to step in sheep dung when he enters the room
** used in sheep pastures
**
*/
void
enter_inv (object Player, object FromRoom) {
   /* execute the standard enter_inv function */
   ::enter_inv();
 
 
   /* only do this for living players */
   if (!(Player->query_prop(LIVE_I_IS))) return;
   if (Player->query_npc()) return;   /* don't add to NPCs */
 
 
   /* if he has already stepped in it, no need to do it again */
   if (present("DUNG_OBJ",Player)) return;
 
   set_this_player(Player);
   write("You step in one of the warm, moist patties with a loud squish!\n");
   write("You get sheep dung all over your feet!\n");
   clone_object(OBJ_DIR+"dung")->move(Player);
}
