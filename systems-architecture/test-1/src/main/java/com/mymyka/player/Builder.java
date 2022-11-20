package com.mymyka.player;

public class Builder implements Player {
    private String name;

    public Builder(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return name;
    }
}
