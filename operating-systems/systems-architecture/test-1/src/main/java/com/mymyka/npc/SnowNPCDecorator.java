package com.mymyka.npc;

public class SnowNPCDecorator extends NPCDecorator {
    public SnowNPCDecorator(NPC npc) {
        super(npc);
    }

    @Override
    public void spawn() {
        super.spawn();
        System.out.println("Snow around started !");
    }
}
