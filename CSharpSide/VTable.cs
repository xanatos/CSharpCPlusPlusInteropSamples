using System;
using System.Runtime.InteropServices;

namespace CSharpSide
{
    public static class VTable
    {
        public static void TestAll()
        {
            var derivedVTablePtr = default(Native.DerivedVTablePtr);

            try
            {
                derivedVTablePtr = Native.NewDerivedVTable(100, 1000);
                //IntPtr ptr = Native.NewVTable(-1);

                Console.WriteLine();

                var vtablePtr = Native.DerivedVTablePtrToVTablePtr(derivedVTablePtr);

                {
                    // IBase1 + IBase2
                    var ibase2Ptr = Native.VTablePtrToIBase2Ptr(vtablePtr);
                    IntPtr vt = Marshal.ReadIntPtr(ibase2Ptr.Ptr);
                    var ibase2 = Marshal.PtrToStructure<Native.IBase2>(vt);

                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method1(new Native.IBase1Ptr { Ptr = ibase2Ptr.Ptr }, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method2(new Native.IBase1Ptr { Ptr = ibase2Ptr.Ptr }, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method3(new Native.IBase1Ptr { Ptr = ibase2Ptr.Ptr }, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase2Method1(ibase2Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase2Method2(ibase2Ptr, 10000)}");
                    Console.WriteLine();
                }

                {
                    // IBase1 + IBase2
                    var ibase2Ptr = Native.VTablePtrToIBase2Ptr(vtablePtr);
                    IntPtr vt = Marshal.ReadIntPtr(ibase2Ptr.Ptr);
                    var ibase2 = Marshal.PtrToStructure<Native.IBase2Plus1>(vt);

                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method1(ibase2Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method2(ibase2Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase1Method3(ibase2Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase2Method1(ibase2Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase2.IBase2Method2(ibase2Ptr, 10000)}");
                    Console.WriteLine();
                }

                {
                    // IBase1 + IBase3
                    var ibase3Ptr = Native.VTablePtrToIBase3Ptr(vtablePtr);
                    IntPtr vt = Marshal.ReadIntPtr(ibase3Ptr.Ptr);
                    var ibase3 = Marshal.PtrToStructure<Native.IBase3Plus1>(vt);

                    Console.WriteLine($"C#, Result: {ibase3.IBase1Method1(ibase3Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase3.IBase1Method2(ibase3Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase3.IBase1Method3(ibase3Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase3.IBase3Method1(ibase3Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase3.IBase3Method2(ibase3Ptr, 10000)}");
                    Console.WriteLine();
                }

                {
                    // IBase4
                    var ibase4Ptr = Native.VTablePtrToIBase4Ptr(vtablePtr);
                    IntPtr vt = Marshal.ReadIntPtr(ibase4Ptr.Ptr);
                    var ibase4 = Marshal.PtrToStructure<Native.IBase4>(vt);

                    Console.WriteLine($"C#, Result: {ibase4.IBase4Method1(ibase4Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase4.IBase4Method2(ibase4Ptr, 10000)}");
                    Console.WriteLine();
                }

                {
                    // IBase5
                    var ibase5Ptr = Native.DerivedVTablePtrToIBase5Ptr(derivedVTablePtr);
                    IntPtr vt = Marshal.ReadIntPtr(ibase5Ptr.Ptr);
                    var ibase5 = Marshal.PtrToStructure<Native.IBase5>(vt);

                    Console.WriteLine($"C#, Result: {ibase5.IBase5Method1(ibase5Ptr, 10000)}");
                    Console.WriteLine($"C#, Result: {ibase5.IBase5Method2(ibase5Ptr, 10000)}");
                    Console.WriteLine();
                }
            }
            finally
            {
                if (derivedVTablePtr.Ptr != IntPtr.Zero)
                {
                    Native.DeleteVTable(Native.DerivedVTablePtrToVTablePtr(derivedVTablePtr));
                }                
            }
        }

        public static class Native
        {
            [StructLayout(LayoutKind.Sequential)]
            public struct VTablePtr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct DerivedVTablePtr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct IBase1Ptr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct IBase2Ptr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct IBase3Ptr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct IBase4Ptr
            {
                public IntPtr Ptr;
            }

            [StructLayout(LayoutKind.Sequential)]
            public struct IBase5Ptr
            {
                public IntPtr Ptr;
            }

            [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
            public delegate int IBase1MethodInt(IBase1Ptr ptr, int par);

            [StructLayout(LayoutKind.Sequential)]
            public class IBase1
            {
                public IBase1MethodInt IBase1Method1;
                public IBase1MethodInt IBase1Method2;
                public IBase1MethodInt IBase1Method3;
            }

            [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
            public delegate int IBase2MethodInt(IBase2Ptr ptr, int par);

            [StructLayout(LayoutKind.Sequential)]
            public class IBase2 : IBase1
            {
                public IBase2MethodInt IBase2Method1;
                public IBase2MethodInt IBase2Method2;
            }

            [StructLayout(LayoutKind.Sequential)]
            public class IBase2Plus1
            {
                public IBase2MethodInt IBase1Method1;
                public IBase2MethodInt IBase1Method2;
                public IBase2MethodInt IBase1Method3;
                public IBase2MethodInt IBase2Method1;
                public IBase2MethodInt IBase2Method2;
            }

            [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
            public delegate int IBase3MethodInt(IBase3Ptr ptr, int par);

            [StructLayout(LayoutKind.Sequential)]
            public class IBase3Plus1
            {
                public IBase3MethodInt IBase1Method1;
                public IBase3MethodInt IBase1Method2;
                public IBase3MethodInt IBase1Method3;
                public IBase3MethodInt IBase3Method1;
                public IBase3MethodInt IBase3Method2;
            }

            [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
            public delegate int IBase4MethodInt(IBase4Ptr ptr, int par);

            [StructLayout(LayoutKind.Sequential)]
            public class IBase4
            {
                public IBase4MethodInt IBase4Method1;
                public IBase4MethodInt IBase4Method2;
            }

            [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
            public delegate int IBase5MethodInt(IBase5Ptr ptr, int par);

            [StructLayout(LayoutKind.Sequential)]
            public class IBase5
            {
                public IBase5MethodInt IBase5Method1;
                public IBase5MethodInt IBase5Method2;
            }

            [DllImport(@"CPlusPlusSide")]
            public static extern VTablePtr NewVTable(int value1);

            [DllImport(@"CPlusPlusSide")]
            public static extern DerivedVTablePtr NewDerivedVTable(int value1, int value2);

            [DllImport(@"CPlusPlusSide")]
            public static extern void DeleteVTable(VTablePtr vt);

            [DllImport(@"CPlusPlusSide")]
            public static extern IBase1Ptr VTablePtrToIBase1Ptr(VTablePtr vt);

            [DllImport(@"CPlusPlusSide")]
            public static extern IBase2Ptr VTablePtrToIBase2Ptr(VTablePtr vt);
     
            [DllImport(@"CPlusPlusSide")]
            public static extern IBase3Ptr VTablePtrToIBase3Ptr(VTablePtr vt);

            [DllImport(@"CPlusPlusSide")]
            public static extern IBase4Ptr VTablePtrToIBase4Ptr(VTablePtr vt);

            [DllImport(@"CPlusPlusSide")]
            public static extern VTablePtr DerivedVTablePtrToVTablePtr(DerivedVTablePtr vt);

            [DllImport(@"CPlusPlusSide")]
            public static extern IBase5Ptr DerivedVTablePtrToIBase5Ptr(DerivedVTablePtr vt);
        }
    }
}
