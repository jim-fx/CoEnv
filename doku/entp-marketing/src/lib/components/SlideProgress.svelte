<script lang="ts">
	import { slideAmount, slideIndex } from '$lib/stores';

	$: alpha = $slideIndex / ($slideAmount - 1);
</script>

{#if alpha < 1}
	<span
		absolute
		bg-white
		style={`width: ${alpha * 100}%; transition: width 0.3s ease; height: 2px;`}
	/>
{/if}
