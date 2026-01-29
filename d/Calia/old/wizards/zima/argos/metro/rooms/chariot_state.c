/* function used for testing of chariot service only */
string query_state() {
   string rstate="Room state:\n-------------------------\n";
 
   rstate=rstate+"This Room:    ";
   if (To) rstate=rstate+(To->query_short())+"\n";
   else    rstate=rstate+"0\n";
 
   rstate=rstate+"StartRoom:    ";
   if (StartRoom()) rstate=rstate+(StartRoom()->query_short())+"\n";
   else           rstate=rstate+"0\n";
 
   rstate=rstate+"DestRoom:    ";
   if (DestRoom()) rstate=rstate+(DestRoom()->query_short())+"\n";
   else          rstate=rstate+"0\n";
 
   rstate=rstate+"location:    "+(location)+"\n";
   rstate=rstate+"chstatus:    "+(chstatus)+"\n";
   rstate=rstate+"increment:   "+(increment)+"\n";
   rstate=rstate+"-------------------------\n";
   return rstate;
}
