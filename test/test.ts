	function padLeft(value: string, padding: number)                       
         function padLeft(value: string, padding: string)                       
         function padLeft(value: string, padding: any) {                        
            if (typeof padding === "number") {                                  
                return String(padding) + value;                                 
            }                                                                   
                                                                                
            if (typeof padding === "string") {                                  
                return padding + value;                                         
            }                                                                   
                                                                                
            throw new Error(`Expected string or number, got \'${padding}\'.`);  
        }                                                                       
                                                                                
        console.log(padLeft("Hello world", 4));