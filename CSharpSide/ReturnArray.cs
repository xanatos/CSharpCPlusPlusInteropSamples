using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class ReturnArray
    {
        public static void TestAll()
        {
            {
                double[] array = ReturnArrayDouble();
                Console.WriteLine($"C# Side, from C, ReturnArrayDouble: {string.Join(", ", array)}");
            }

            {
                Native.PassOutArrayDouble(out double[] array, out int count);
                Console.WriteLine($"C# Side, from C, PassOutArrayDouble: {string.Join(", ", array)}");
            }

            {
                var lst = new List<double>();
                Native.PassOutThroughDelegateArrayDouble(lst.Add); // or x => lst.Add(x)
                Console.WriteLine($"C# Side, from C, PassOutThroughDelegateArrayDouble: {string.Join(", ", lst)}");
            }
        }

        public static double[] ReturnArrayDouble()
        {
            IntPtr ptr = Native.ReturnArrayDouble(out int count);

            var array = new double[count];
            Marshal.Copy(ptr, array, 0, count);

            // Or use malloc in C and expose a FreeMalloc()
            Marshal.FreeCoTaskMem(ptr);

            return array;
        }

        public static class Native
        {
            [DllImport(@"CSide")]
            public static extern IntPtr ReturnArrayDouble(out int count);

            [DllImport(@"CSide")]
            public static extern void PassOutArrayDouble([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] out double[] array, out int count);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate void AddDouble(double dbl);

            [DllImport(@"CSide")]
            public static extern void PassOutThroughDelegateArrayDouble(AddDouble add);
        }
    }
}
