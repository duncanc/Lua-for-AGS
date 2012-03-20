namespace AGS.Plugin.Lua
{
    partial class CodeConvertPane
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.agsCodeEntry = new System.Windows.Forms.TextBox();
            this.luaCodeOutput = new System.Windows.Forms.TextBox();
            this.convertButton = new System.Windows.Forms.Button();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // agsCodeEntry
            // 
            this.agsCodeEntry.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.agsCodeEntry.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.agsCodeEntry.Location = new System.Drawing.Point(0, 0);
            this.agsCodeEntry.MaxLength = 1032767;
            this.agsCodeEntry.Multiline = true;
            this.agsCodeEntry.Name = "agsCodeEntry";
            this.agsCodeEntry.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.agsCodeEntry.Size = new System.Drawing.Size(271, 322);
            this.agsCodeEntry.TabIndex = 0;
            this.agsCodeEntry.Text = "// AGS Script Code Input";
            this.agsCodeEntry.WordWrap = false;
            // 
            // luaCodeOutput
            // 
            this.luaCodeOutput.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.luaCodeOutput.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.luaCodeOutput.Location = new System.Drawing.Point(0, 0);
            this.luaCodeOutput.MaxLength = 1032767;
            this.luaCodeOutput.Multiline = true;
            this.luaCodeOutput.Name = "luaCodeOutput";
            this.luaCodeOutput.ReadOnly = true;
            this.luaCodeOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.luaCodeOutput.Size = new System.Drawing.Size(268, 325);
            this.luaCodeOutput.TabIndex = 1;
            this.luaCodeOutput.Text = "-- Lua Script Code Output";
            this.luaCodeOutput.WordWrap = false;
            this.luaCodeOutput.TextChanged += new System.EventHandler(this.luaCodeOutput_TextChanged);
            // 
            // convertButton
            // 
            this.convertButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.convertButton.Location = new System.Drawing.Point(3, 331);
            this.convertButton.Name = "convertButton";
            this.convertButton.Size = new System.Drawing.Size(552, 25);
            this.convertButton.TabIndex = 2;
            this.convertButton.Text = "Convert";
            this.convertButton.UseVisualStyleBackColor = true;
            this.convertButton.Click += new System.EventHandler(this.convertButton_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.agsCodeEntry);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.luaCodeOutput);
            this.splitContainer1.Size = new System.Drawing.Size(552, 325);
            this.splitContainer1.SplitterDistance = 273;
            this.splitContainer1.SplitterWidth = 8;
            this.splitContainer1.TabIndex = 3;
            // 
            // CodeConvertPane
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.convertButton);
            this.Name = "CodeConvertPane";
            this.Size = new System.Drawing.Size(558, 357);
            this.Load += new System.EventHandler(this.CodeConvertPane_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox agsCodeEntry;
        private System.Windows.Forms.TextBox luaCodeOutput;
        private System.Windows.Forms.Button convertButton;
        private System.Windows.Forms.SplitContainer splitContainer1;
    }
}
