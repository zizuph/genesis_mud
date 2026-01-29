object *satyr=allocate(NumSatyrs);
void reset_room() {
    int i;
    for (i=0; i<NumSatyrs; i++)
       if (!(satyr[i])) {
          satyr[i]=clone_object(NPC_DIR+"satyr");
          satyr[i]->equip_me();
          satyr[i]->move(THIS);
          tell_room(THIS, QCNAME(satyr[i])+" jumps from behind a tree.\n");
      }
}
