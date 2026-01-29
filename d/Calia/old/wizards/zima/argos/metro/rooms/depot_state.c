string query_state() {
   object To=this_object();
   string rstate="Room state:\n-------------------------\n";
 
   rstate=rstate+"This Room:    ";
   if (To) rstate=rstate+(To->query_short())+"\n";
   else    rstate=rstate+"0\n";
 
   rstate=rstate+"chariot_room: ";
   if (chariot_room()) rstate=rstate+(chariot_room()->query_short())+"\n";
   else              rstate=rstate+"0\n";
 
   rstate=rstate+"chariot obj: ";
   if (chariot) rstate=rstate+"here\n";
   else         rstate=rstate+"not here\n";
 
   rstate=rstate+"attendant:   ";
   if (attendant) rstate=rstate+"here\n";
   else           rstate=rstate+"not here\n";
 
   rstate=rstate+"waiting:     "+waiting+"\n";
   rstate=rstate+"char_signal: "+(chariot_signaled)+"\n";
   rstate=rstate+"char_here:   "+(chariot_here)+"\n";
   rstate=rstate+"-------------------------\n";
   return rstate;
}
