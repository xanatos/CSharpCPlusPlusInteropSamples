using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpSide
{
    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine($"Program is running at {(Environment.Is64BitProcess ? 64 : 32)} bits");
            Console.WriteLine($"Running under {RuntimeInformation.FrameworkDescription}");
            Console.WriteLine();

#if NETCOREAPP
            // This works with.NET Core.
            var alreadyLogged = new System.Collections.Generic.HashSet<string>();

            NativeLibrary.SetDllImportResolver(typeof(Program).Assembly, (libraryName, assembly, searchPath) =>
            {
                IntPtr ptr;

                // If the standard loader can find the library, then no problems
                if (NativeLibrary.TryLoad(libraryName, assembly, searchPath, out ptr))
                {
                    return ptr;
                }

                // The the standard loader couldn't find the library, let's check
                // the x64 or the x86 folder.
                string path = Environment.Is64BitProcess ? "x64" : "x86";
                string relativePath = System.IO.Path.Combine(path, libraryName);

                // Note that this method is called *once* for each DllImport
                if (alreadyLogged.Add(relativePath))
                {
                    Console.WriteLine($"Loding {relativePath}");
                }

                ptr = NativeLibrary.Load(relativePath);
                return ptr;
            });
#else
            // This is for .NET Framework, and it is "manual", you must list all
            // the native dll you want to load
            Utils.SimpleDllLoader("CSide");
            Utils.SimpleDllLoader("CPlusPlusSide");
#endif

            // Disable caching of memory of BSTR
            CoMallocSpy.Native.SetOaNoCache();

            // Warm-up of the BSTR memory allocator
            Marshal.FreeBSTR(Marshal.StringToBSTR(string.Empty));

            var spy = CoMallocSpy.Native.Start();

            // Debugger on memory allocation
            //CoMallocSpy.Native.SetBreakAlloc(spy, 14);

            Console.OutputEncoding = Encoding.UTF8;

            ReturnArray.TestAll();
            ReturnArrayString.TestAll();
            ReturnArrayStruct.TestAll();
            SafeArray.TestAll();
            PassString.TestAll();
            ReturnString.TestAll();

            MyClass.TestAll();
            VTable.TestAll();

            Console.WriteLine();

            CoMallocSpy.Native.Dump(spy, Console.Write);
            CoMallocSpy.Native.Dump(spy, x => Debug.Write(x));
            
            bool res = CoMallocSpy.Native.Stop();
            Console.WriteLine($"CoMallocSpy {(res ? "stopped" : "delayed stopping")}");
        }
    }
}
