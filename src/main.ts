import { Run } from './compiler';

declare var process: any;

try {
    new Run().run(Run.processFiles(process.argv), 'lua', Run.processOptions(process.argv));
} catch (e) {
    if (e.message.indexOf(`Could not find a valid 'tsconfig.json'`) !== -1) {
        print();
    } else {
        console.error(e.stack);
    }
}

function print() {
    console.log(`Version 1.0.10
    Syntax:   tsc-lua [options] [file...]

    Examples: tsc-lua hello.ts
              tsc-lua --jslib file.ts
              tsc-lua tsconfig.json
              tsc-lua

    Options:
     -jslib                                             Use JS library.
     -singleModule                                      Output single file.
     -varAsLet                                          Use all 'var' variables as 'let'.
     `);
}
