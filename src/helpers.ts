import * as ts from 'typescript';

export class Helpers {
    public static isConstOrLet(node: ts.Node): boolean {
        return (node.flags & ts.NodeFlags.Let) === ts.NodeFlags.Let || (node.flags & ts.NodeFlags.Const) === ts.NodeFlags.Const;
    }

    public static isConst(node: ts.Node): boolean {
        return (node.flags & ts.NodeFlags.Const) === ts.NodeFlags.Const;
    }

    public static isLet(node: ts.Node): boolean {
        return (node.flags & ts.NodeFlags.Let) === ts.NodeFlags.Let;
    }

    public static correctFileNameForLua(filePath: string): string {
        // fix filename
        let fileNameIndex = filePath.lastIndexOf('\\');
        if (fileNameIndex === -1) {
            fileNameIndex = filePath.lastIndexOf('/');
        }

        const fileName = fileNameIndex >= 0 ? filePath.substr(fileNameIndex + 1) : filePath;

        const extIndex = fileName.lastIndexOf('.');
        const fileNameNoExt = extIndex >= 0 ? fileName.substr(0, extIndex) : fileName;

        const fileNameFixed = fileNameNoExt.replace(/\./g, '_');

        // rebuild filePath
        const beginPath = fileNameIndex >= 0 ? filePath.substr(0, fileNameIndex + 1) : '';
        const endExt = extIndex >= 0 ? fileName.substr(extIndex) : '';

        return beginPath + fileNameFixed + endExt;
    }
}
