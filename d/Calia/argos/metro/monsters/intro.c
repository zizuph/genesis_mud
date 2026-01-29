/* standardized introduction code for NPC's in Argos                      */
/* assumes intro_resp_cmd array declared before included                  */
string *intro_list=(({}));
 
/* if new met player, add name to list & return 1, else return 0 */
int check_intro(string name) {
   if (member_array(name,intro_list)>-1) return 0;
   intro_list=intro_list + ({name});
   return 1;
}
 
void respond_to_intro() {
   int i;
   for (i=0; i<sizeof(intro_resp_cmd); i++)
      this_object()->command(intro_resp_cmd[i]);
}
 
public void add_introduced(string name) {
   if (this_player()->query_npc())
   {
      return;
   }
   
   mapping introductions = this_player()->query_introduced();
   string name = this_object()->query_real_name();
   if (!strlen(name))
   {
      // Without a real name, we don't do anything
      return;
   }
   
   // We introduce back if the person introducing doesn't know us.
   if (!introductions[name])
   {
      set_alarm(2.0,0.0,"respond_to_intro");
   }
}
