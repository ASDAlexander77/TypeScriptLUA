function __get_call_undefined__(t, k) {
    let get_: object = rawget(t, "__get__");
    let getmethod: object = get_ && get_[k];
    if (getmethod !== null) {
        return getmethod(t);
    }

    let proto: object = rawget(t, "__proto");

    while (proto !== null) {
        let v = rawget(proto, k);
        if (v === null) {
            const nullsHolder: object = rawget(t, "__nulls");
            if (nullsHolder && nullsHolder[k]) {
                return null;
            }
        } else {
            return v;
        }

        get_ = rawget(proto, "__get__");
        getmethod = get_ && get_[k];
        if (getmethod !== null) {
            return getmethod(t);
        }

        proto = rawget(proto, "__proto");
    }

    return undefined;
}

function __set_call_undefined__(t, k, v) {
    let proto: object = t;
    while (proto !== null) {
        let set_: object = rawget(proto, "__set__");
        const setmethod: object = set_ && set_[k];
        if (setmethod !== null) {
            setmethod(t, v);
            return;
        }

        proto = rawget(proto, "__proto");
    }

    if (v === null) {
        const nullsHolder: object = rawget(t, "__nulls");
        if (nullsHolder === null) {
            nullsHolder = {};
            rawset(t, "__nulls", nullsHolder);
        }

        nullsHolder[k] = true;
        return;
    }

    let v0 = v;
    if (v === undefined) {
        const nullsHolder: object = rawget(t, "__nulls");
        if (nullsHolder !== null) {
            nullsHolder[k] = null;
        }

        v0 = null;
    }

    rawset(t, k, v0);
}

function __decorate(
    decors: any[], proto: any, propertyName: string, descriptorOrParameterIndex: any | undefined | null) {
    const isClassDecorator = propertyName === undefined;
    const isMethodDecoratorOrParameterDecorator = descriptorOrParameterIndex !== undefined;

    let protoOrDescriptorOrParameterIndex = isClassDecorator
        ? proto
        : null === descriptorOrParameterIndex
            ? descriptorOrParameterIndex = Object.getOwnPropertyDescriptor(proto, propertyName)
            : descriptorOrParameterIndex;

    for (let l = decors.length - 1; l >= 0; l--) {
        const decoratorItem = decors[l];
        if (decoratorItem) {
            protoOrDescriptorOrParameterIndex =
                (isClassDecorator
                    ? decoratorItem(protoOrDescriptorOrParameterIndex)
                    : isMethodDecoratorOrParameterDecorator
                        ? decoratorItem(proto, propertyName, protoOrDescriptorOrParameterIndex)
                        : decoratorItem(proto, propertyName))
                || protoOrDescriptorOrParameterIndex;
        }
    }

    if (isMethodDecoratorOrParameterDecorator && protoOrDescriptorOrParameterIndex) {
        Object.defineProperty(proto, propertyName, protoOrDescriptorOrParameterIndex);
    }

    return protoOrDescriptorOrParameterIndex;
}

import './JS';

declare var os: any;
declare var navigator: any;

navigator = <Navigator>{};

// Core
import './BABYLON/Materials/babylon_effect';
import './BABYLON/babylon_types';
import './BABYLON/Events/babylon_keyboardEvents';
import './BABYLON/Events/babylon_pointerEvents';
import './BABYLON/Math/babylon_math';
import './BABYLON/Math/babylon_math_scalar';
import './BABYLON/babylon_mixins';
import './BABYLON/Tools/babylon_decorators';
import './BABYLON/Tools/babylon_deferred';
import './BABYLON/Tools/babylon_observable';
import './BABYLON/Tools/babylon_smartArray';
import './BABYLON/Tools/babylon_tools';
import './BABYLON/Tools/babylon_promise';
import './BABYLON/Tools/babylon_workerPool';
import './BABYLON/States/babylon_alphaCullingState';
import './BABYLON/States/babylon_depthCullingState';
import './BABYLON/States/babylon_stencilState';
import './BABYLON/Engine/babylon_engine';
import './BABYLON/Engine/babylon_webgl2';
// import './BABYLON/Engine/babylon_nullEngine';
import './BABYLON/babylon_node';
import './BABYLON/Culling/babylon_boundingSphere';
import './BABYLON/Culling/babylon_boundingBox';
import './BABYLON/Culling/babylon_boundingInfo';
import './BABYLON/Mesh/babylon_transformNode';
import './BABYLON/Mesh/babylon_abstractMesh';
import './BABYLON/Lights/babylon_light';
import './BABYLON/Cameras/babylon_camera';
import './BABYLON/Rendering/babylon_renderingManager';
import './BABYLON/Rendering/babylon_renderingGroup';
import './BABYLON/babylon_sceneComponent';
import './BABYLON/babylon_abstractScene';
import './BABYLON/babylon_scene';
import './BABYLON/babylon_assetContainer';
import './BABYLON/Mesh/babylon_buffer';
import './BABYLON/Mesh/babylon_vertexBuffer';
import './BABYLON/Materials/Textures/babylon_internalTextureLoader';
import './BABYLON/Materials/Textures/babylon_internalTextureTracker';
import './BABYLON/Materials/Textures/babylon_internalTexture';
import './BABYLON/Materials/Textures/babylon_baseTexture';
import './BABYLON/Materials/Textures/babylon_texture';
import './BABYLON/Mesh/babylon_mesh';
import './BABYLON/Mesh/babylon_subMesh';
import './BABYLON/Materials/babylon_material';
import './BABYLON/Materials/babylon_uniformBuffer';
import './BABYLON/Mesh/babylon_mesh_vertexData';
import './BABYLON/Mesh/babylon_geometry';
import './BABYLON/Tools/babylon_performanceMonitor';
import './BABYLON/Materials/babylon_materialHelper';
import './BABYLON/Materials/babylon_pushMaterial';
import './BABYLON/Materials/babylon_standardMaterial';
import './BABYLON/Mesh/babylon_groundMesh';

// extra
import './BABYLON/Mesh/babylon_meshBuilder';

import './BABYLON/Cameras/babylon_targetCamera';
import './BABYLON/Cameras/babylon_cameraInputsManager';

import './BABYLON/Cameras/Inputs/babylon_arcRotateCameraKeyboardMoveInput';
import './BABYLON/Cameras/Inputs/babylon_arcRotateCameraMouseWheelInput';
import './BABYLON/Cameras/Inputs/babylon_arcRotateCameraPointersInput';
import './BABYLON/Cameras/babylon_arcRotateCameraInputsManager';
import './BABYLON/Cameras/babylon_arcRotateCamera';

import './BABYLON/Cameras/Inputs/babylon_freeCameraKeyboardMoveInput';
import './BABYLON/Cameras/Inputs/babylon_freeCameraMouseInput';
import './BABYLON/Cameras/babylon_freeCameraInputsManager';
import './BABYLON/Cameras/babylon_freeCamera';

import './BABYLON/Tools/babylon_filesInput';

import './BABYLON/Lights/babylon_hemisphericLight';

import './BABYLON/Materials/babylon_imageProcessingConfiguration';
import './BABYLON/Materials/babylon_colorCurves';

import './BABYLON/Culling/babylon_ray';
import './BABYLON/Collisions/babylon_pickingInfo';

import './BABYLON/Loading/babylon_sceneLoader';
import './BABYLON/Tools/babylon_database';
import './BABYLON/Loading/Plugins/babylon_babylonFileLoader';

import './BABYLON/Gamepad/babylon_gamepad';
import './BABYLON/Gamepad/babylon_gamepadManager';

import './BABYLON/Cameras/Inputs/babylon_freeCameraTouchInput';
import './BABYLON/Cameras/Inputs/babylon_freeCameraGamepadInput';
import './BABYLON/Cameras/babylon_touchCamera';
import './BABYLON/Cameras/babylon_universalCamera';
import './BABYLON/Gamepad/babylon_gamepadSceneComponent';

import './BABYLON/Lights/babylon_shadowLight';
import './BABYLON/Lights/babylon_pointLight';

import './BABYLON/PostProcess/babylon_postProcessManager';
import './BABYLON/PostProcess/babylon_postProcess';
import './BABYLON/PostProcess/babylon_passPostProcess';

import WindowEx from './window';
import DocumentEx from './document';
import Image from './image';
// @ts-ignore
import Canvas from './canvas';
import TestApp from './testapp';
import TestApp2 from './testapp2';
import TestLoadMesh from './testloadmesh';

declare var window: WindowEx;
window = new WindowEx();

declare var setTimeout: (funct: any, millisec: number) => number;
setTimeout = WindowEx.setTimeout;

declare var document: DocumentEx;
document = new DocumentEx();

// hack to fix BabylonJS 3.3 code
// @ts-ignore
BABYLON.Viewport.toGlobal = function (renderWidth: number, renderHeight: number): BABYLON.Viewport {
    return new BABYLON.Viewport(this.x * renderWidth, this.y * renderHeight, this.width * renderWidth, this.height * renderHeight);
};

new TestApp2().run();

// @ts-ignore
window.focus();
// @ts-ignore
window.loop();
