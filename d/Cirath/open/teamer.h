static object leader;

varargs void
bring_room_team (string lpath, int larm, int fnum, string fpath, int farm)
{
    int count;
    if(!objectp(leader))
    {
        leader = clone_object(lpath);
        if(larm)
            leader->arm_me();
        leader->move_living("into the room", TO);
        if(!(fpath))
            {
                fpath = lpath;
                farm  = larm;
            }

        for(count=0; count < fnum; count ++)
        {
            object follower=clone_object(fpath);
            if(farm)
                follower->arm_me();
            follower->move_living("into the room", TO);
            leader->team_join(follower);
        }

    }    
}
