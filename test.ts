export interface IBehaviorAware<T> {
    init(): void;
}

class Node implements IBehaviorAware<Node> {
    public metadata: any = null;

    public animations = new Array<Animation>();

    constructor(scene: any = null) {
    }

    public init() {
    }

    public set x(v) {
    }

    public get x() {
        return 0;
    }
}

class TargetCamera extends Node {
    constructor() {
        super();
    }

    public set x1(v) {
    }

    public get x1() {
        return 1;
    }
}

class ArcCamera extends TargetCamera {
    constructor() {
        super();
    }

    public set x2(v) {
    }

    public get x2() {
        return 2;
    }
}

console.log(new ArcCamera());
