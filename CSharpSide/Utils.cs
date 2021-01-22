using System;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class Utils
    {
        public static void SimpleDllLoader(string libraryName)
        {
            string path = Environment.Is64BitProcess ? "x64" : "x86";
            string relativePath = Path.Combine(path, libraryName);
            Console.WriteLine($"Loding {relativePath}");

            if (Native.LoadLibrary(relativePath) == IntPtr.Zero)
            {
                throw new Win32Exception();
            }
        }

        /// <summary>
        /// Replacement for the missing Marshal.PtrToStringUTF8
        /// </summary>
        /// <param name="ptr"></param>
        /// <returns></returns>
        public static string PtrToStringUTF8(IntPtr ptr)
        {
            return Marshal.PtrToStructure<Utf8String>(ptr).String;
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct Utf8String
        {
            [MarshalAs(UnmanagedType.LPUTF8Str)]
            public string String;
        }

        public static class Native
        {
            [DllImport(@"CSide")]
            public static extern void FreeMalloc(IntPtr ptr);

            [DllImport("kernel32", SetLastError = true)]
            public static extern IntPtr LoadLibrary(string lpFileName);
        }

    }
}
