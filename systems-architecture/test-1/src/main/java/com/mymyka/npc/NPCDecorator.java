package com.mymyka.npc;

import com.mymyka.player.Player;

public abstract class NPCDecorator implements NPC {
    protected NPC npc;

    public NPCDecorator(NPC npc) {
        this.npc = npc;
    }

    @Override
    public void sayHello(Player player) {
        npc.sayHello(player);
    }
}
